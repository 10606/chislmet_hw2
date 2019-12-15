#include "predictor_corrector.h"
#include "method_utils.h"
#include <iostream>
#include <vector>
#include <cassert>

void print(std::vector<std::vector<double>> const& X) {
	int n_step = 100;
	int k_step = 10;
	for (size_t n = 0; n < X[0].size(); n += n_step) {
		for (size_t k = 0; k < X.size(); k += k_step) {
			std::cout << X[k][n] << ' ';
		}
		std::cout << std::endl;
	}
}

void print(std::vector<double> const& v, size_t step) {
	for (size_t i = 0; i < v.size(); i += step) {
		std::cout << v[i] << ' ';
	}
	std::cout << std::endl;
}

void calcW(
	std::vector<std::vector<double>> const& X,
	std::vector<std::vector<double>> const& T,
	std::vector<std::vector<double>>& W,
	Params const& params) {
	for (size_t i = 0; i < X.size(); i++) {
		for (size_t j = 0; j < X[i].size(); j++) {
			W[i][j] = -params.W(X[i][j], T[i][j]);
		}
	}
}

Solution solve(Params const& params) {
	size_t L = params.L();
	size_t N = params.N();
	//std::cout << "delta_t delta_z == " << params.delta_t << ' ' << params.delta_z << std::endl;
	//std::cout << "max_t max_z == " << params.max_t << ' ' << params.max_z << std::endl;
	//std::cout << "L N == " << L << ' ' << N << std::endl;
	std::vector<std::vector<double>> X(L, std::vector<double>(N));
	std::vector<std::vector<double>> T(L, std::vector<double>(N));
	std::vector<std::vector<double>> W(L, std::vector<double>(N));

	for (size_t n = 0; n < N; n++) {
		X[0][n] = 0;
		T[0][n] = params.Tm;
	}

	X[0][0] = 0;
	T[0][0] = params.Tm;
	for (size_t k = 1; k < L; k++) {
		X[k][0] = 1;
		T[k][0] = params.T0;
	}
	//print(X);
	for (size_t n = 0; n < N - 1; n++) {
		for (size_t k = 1; k < L - 1; k++) {
			double dz2 = params.delta_z * params.delta_z;
			/*
			X[k][n + 1] = X[k][n] + params.delta_t * (
				params.D * (X[k + 1][n] - 2 * X[k][n] + X[k - 1][n]) / dz2 +
				params.W(X[k][n], T[k][n]));
			T[k][n + 1] = T[k][n] + params.delta_t * (
				params.kappa() * (T[k + 1][n] - 2 * T[k][n] + T[k - 1][n]) / dz2 -
				params.Q / params.C * params.W(X[k][n], T[k][n]));
			*/

			double mod_W = params.W(X[k][n], T[k][n], params.alpha - 1);
			X[k][n + 1] = (X[k][n] + params.D * params.delta_t / dz2 * (X[k + 1][n] - 2 * X[k][n] + X[k - 1][n])) /
				(1 + params.delta_t * mod_W);

			T[k][n + 1] = T[k][n] + params.delta_t * (
				params.kappa() * (T[k + 1][n] - 2 * T[k][n] + T[k - 1][n]) / dz2 +
				params.Q / params.C * (X[k][n + 1] * mod_W));

		}
		//X[L - 1][n + 1] = X[L - 2][n + 1] + (X[L - 1][n] - X[L - 3][n]) * 0.5;
		//X[L - 1][n + 1] = T[L - 2][n + 1] + (T[L - 1][n] - T[L - 3][n]) * 0.5;
		X[L - 1][n + 1] = X[L - 2][n + 1];
		T[L - 1][n + 1] = T[L - 2][n + 1];


		if (!params.doCorrection) {
			calcW(X, T, W, params);
			continue;
		}
		std::vector<quard<double>> system;
		double a = -params.D * params.delta_t / (params.delta_z * params.delta_z);
		double b = 1 - 2 * a;
		double c = X[1][n] + params.delta_t * params.W(X[1][n + 1], T[1][n + 1]);
		system.push_back({ 0, b, a, c });
		for (size_t k = 2; k < L - 1; k++) {
			c = X[k][n] + params.delta_t * params.W(X[k][n + 1], T[k][n + 1]);
			system.push_back({ a, b, a, c });
		}
		c = X[L - 1][n] + params.delta_t * params.W(X[L - 1][n + 1], T[L - 1][n + 1]);
		system.push_back({ a, 1 - a, 0, c });

		std::vector<double> Xs = solve_3_diag(system);
		for (size_t k = 1; k < L; k++) {
			/*if (Xs[k - 1] < 0 || Xs[k - 1] > 1) {
				std::cerr << "Xs[k - 1] == " << Xs[k - 1] << std::endl;
			}*/
			/*if (Xs[k - 1] < 0) {
				Xs[k - 1] = -1;
			}
			if (Xs[k - 1] > 1) {
				Xs[k - 1] = 2;
			}*/
			//assert((!std::isnan(Xs[k - 1])));
			//assert(Xs[k - 1] == Xs[k - 1]);
			//X[k][n + 1] = clamp(Xs[k - 1], 0, 10);
			X[k][n + 1] = Xs[k - 1];
		}
		X[L - 1][n + 1] = X[L - 2][n + 1];
		system.clear();


		a = -params.kappa() * params.delta_t / (params.delta_z * params.delta_z);
		b = 1 - 2 * a;
		c = T[1][n] - a * params.Tm - params.delta_t * params.Q / params.C * params.W(X[1][n + 1], T[1][n + 1]);
		system.push_back({ 0, b, a, c });
		for (size_t k = 2; k < L - 1; k++) {
			c = T[k][n] - params.delta_t * params.Q / params.C * params.W(X[k][n + 1], T[k][n + 1]);
			system.push_back({ a, b, a, c });
		}
		c = T[L - 1][n] - params.delta_t * params.Q / params.C * params.W(X[L - 1][n + 1], T[L - 1][n + 1]);
		system.push_back({ a, 1 - a, 0, c });
		std::vector<double> Ts = solve_3_diag(system);
		for (size_t k = 1; k < L; k++) {
			//assert(Ts[k - 1] == Ts[k - 1]);
			T[k][n + 1] = Ts[k - 1];
			//T[k][n + 1] = clamp(Ts[k - 1], params.T0, params.Tm * 10);
		}
		T[L - 1][n + 1] = T[L - 2][n + 1];
		system.clear();
	}

	calcW(X, T, W, params);

	return { X, T, W };
}
