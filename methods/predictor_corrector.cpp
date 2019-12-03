#include "predictor_corrector.h"
#include "method_utils.h"
#include <iostream>
#include <vector>

void print(std::vector<std::vector<double>> const& X) {
	for (size_t n = 0; n < X[0].size(); n++) {
		for (size_t k = 0; k < X.size(); k++) {
			std::cout << X[k][n] << ' ';
		}
		std::cout << std::endl;
	}
}

Solution solve(Params const& params) {
	size_t L = static_cast<size_t>(params.max_z / params.delta_z) + 1;
	size_t N = static_cast<size_t>(params.max_t / params.delta_t) + 1;
	std::cout << "delta_t delta_z == " << params.delta_t << ' ' << params.delta_z << std::endl;
	std::cout << "max_t max_z == " << params.max_t << ' ' << params.max_z << std::endl;
	std::cout << "L N == " << L << ' ' << N << std::endl;
	std::vector<std::vector<double>> X(L, std::vector<double>(N));
	std::vector<std::vector<double>> T(L, std::vector<double>(N));

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
			X[k][n + 1] = X[k][n] + params.delta_t * (
				params.D * (X[k + 1][n] - 2 * X[k][n] + X[k - 1][n]) / dz2 +
				params.W(X[k][n], T[k][n]));
			T[k][n + 1] = T[k][n] + params.delta_t * (
				params.kappa() * (T[k + 1][n] - 2 * T[k][n] + T[k - 1][n]) / dz2 -
				params.Q / params.C * params.W(X[k][n], T[k][n]));
		}
		X[L - 1][n + 1] = X[L - 2][n + 1];
		T[L - 1][n + 1] = T[L - 2][n + 1];
	}

	//print(X);
	//std::cout << std::endl;

	if (!params.doCorrection) {
		return { X, T };
	}

	std::vector<quard<double>> system;
	double a = -params.D * params.delta_t / (params.delta_z * params.delta_z);
	double b = 1 - 2 * a;
	for (size_t n = 0; n < N - 1; n++) {
		double c = X[1][n] + params.delta_t * params.W(X[1][n + 1], T[1][n + 1]);
		system.push_back({ 0, b, a, c });
		for (size_t k = 2; k < L - 1; k++) {
			c = X[k][n] + params.delta_t * params.W(X[k][n + 1], T[k][n + 1]);
			system.push_back({ a, b, a, c });
		}
		c = X[L - 1][n] + params.delta_t * params.W(X[L - 1][n + 1], T[L - 1][n + 1]);
		system.push_back({ 1 - a, a, 0, c });
		std::vector<double> Xs = solve_3_diag(system);
		for (size_t k = 1; k < L; k++) {
			X[k][n + 1] = Xs[k - 1];
		}
	}

	system.clear();
	a = -params.kappa() * params.delta_t / (params.delta_z * params.delta_z);
	b = 1 - 2 * a;
	for (size_t n = 0; n < N - 1; n++) {
		double c = T[1][n] - a * params.Tm - params.delta_t * params.Q / params.C * params.W(X[1][n + 1], T[1][n + 1]);
		system.push_back({ 0, b, a, c });
		for (size_t k = 1; k < L - 1; k++) {
			c = T[k][n] - params.delta_t * params.Q / params.C * params.W(X[k][n + 1], T[k][n + 1]);
			system.push_back({ a, b, a, c });
		}
		c = T[L - 1][n] - params.delta_t * params.Q / params.C * params.W(X[L - 1][n + 1], T[L - 1][n + 1]);
		system.push_back({ 1 - a, a, 0, c });
		std::vector<double> Ts = solve_3_diag(system);
		for (size_t k = 1; k < L; k++) {
			T[k][n + 1] = Ts[k - 1];
		}
	}

	return { X, T };
}
