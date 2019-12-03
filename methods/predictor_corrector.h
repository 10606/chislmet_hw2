#ifndef PREDICTOR_CORRECTOR_H
#define PREDICTOR_CORRECTOR_H

#include <vector>
#include <cmath>

struct Params {
	double K = 1.6e6;
	double E = 8e4;
	double alpha = 2; // 0.5 - 3
	double Q = 7e5;
	double T0 = 293;
	double rho = 830;
	double C = 1990;
	double lambda = 0.13;
	double D = 7.87067869467e-8;
	double R = 8.31446261815324;
	double Tm = T0 + Q / C;

	//double delta_t = U() * 1800;
	//double delta_z = deltaH() * 0.1;
	double delta_t = U() * 1;
	double delta_z = deltaH() * 0.1;
	double max_z = delta_z * 10;
	double max_t = delta_t * 1000;
	bool doCorrection = false;

	double kappa() const {
		return lambda / (rho * C);
	}

	double W(double X, double T) const {
		return -K * pow(X, alpha) * exp(-E / (R * T));
	}

	double U() const {
		double tmp = (R * Tm * Tm / E);
		return sqrt(2 * K * lambda / (Q * rho * (Q / C)) * T0 / Tm * tmp * tmp * exp(-E / (R * Tm)));
	}

	double deltaH() const {
		return kappa() / U();
	}
};

struct Solution {
	std::vector<std::vector<double>> X, T;
};

Solution solve(Params const& params);

#endif
