#include <iostream>
#include "predictor_corrector.h"

int main() {
	FILE* f = freopen("output.txt", "w", stdout);

	Params params;
	/*std::cout << params.deltaH() << std::endl;
	return 0;*/
	Solution solution = solve(params);
	auto X = solution.X;
	auto T = solution.T;
	//std::cout << std::endl;
	//print(X);
	for (size_t k = 0; k < X.size(); k++) {
		std::cout << "(" << k * params.delta_z << ";" << X[k][X[0].size() - 1] << ")" << std::endl;
	}
	/*for (size_t k = 0; k < T.size(); k++) {
		std::cout << "(" << k * params.delta_t << ";" << T[k][10] << ")" << std::endl;
	}*/
}
