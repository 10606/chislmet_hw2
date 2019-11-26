#include <iostream>
#include <sstream>
#include <string>
#include <functional>
#include "methods/cheharda.h"
#include "methods/implicit_forward_flow.h"
#include "methods/implicit_backward_flow.h"
#include "methods/explicit_forward_flow.h"
#include "methods/explicit_backward_flow.h"
#include "methods/method_utils.h"
#include "plots/images_generator.h"
#include "plots/start_parameters.h"

double const DEFAULT_DELTA_X = 0.1;
double const DEFAULT_DELTA_T = 0.1;

void readConditions(std::function <double (double)>& res) {
    std::string s;
    getline(std::cin, s);
    if (s == "") {
        return;
    }
    std::istringstream ss(s);
    std::string functionName;
    double a, b, c, d;
    ss >> functionName;
    if (functionName == "step") {
        ss >> a >> b;
        res = T_step(a, b);
    } else if (functionName == "rectangle") {
        ss >> a >> b >> c >> d;
        res = T_rectangle(a, b, c, d);
    } else if (functionName == "sin") {
        ss >> a >> b >> c;
        res = T_sin(a, b, c);
    }
}

int main () {
    double delta_x, delta_t, u, kappa, r, s;
    std::pair<double, double> x_range, t_range;
    std::cout << "delta_x = ";
    std::string dx;
    std::getline(std::cin, dx);
    if (dx == "") {
        delta_x = DEFAULT_DELTA_X;
        delta_t = DEFAULT_DELTA_T;
        std::cout << "delta_x = " << delta_x << std::endl;
        std::cout << "delta_t = " << delta_t << std::endl;
    } else {
        delta_x = std::stod(dx);
        std::cout << "delta_t = ";
        std::cin >> delta_t;
        std::cin.ignore();
    }
    std::cout << "u = ";
    std::string tmp;
    std::getline(std::cin, tmp);
    if (tmp == "") {
        std::cout << "r = ";
        std::cin >> r;
        std::cout << "s = ";
        std::cin >> s;
        u = calc_u(s, delta_x, delta_t);
        kappa = calc_kappa(r, delta_x, delta_t);
        std::cout << "u = " << u << std::endl;
        std::cout << "kappa = " << kappa << std::endl;
    } else {
        u = std::stod(tmp);
        std::cout << "kappa = ";
        std::cin >> kappa;
        r = calc_r(u, kappa, delta_x, delta_t);
        s = calc_s(u, kappa, delta_x, delta_t);
        std::cout << "r = " << r << std::endl;
        std::cout << "s = " << s << std::endl;
    }

    std::cout << "[space separated] x_range = ";
    std::cin >> x_range.first >> x_range.second;
    t_range.first = 0;
    std::cout << "simulation_time = ";
    std::cin >> t_range.second;
    std::cout << "[bitmask] if ib ef eb ch: ";
    std::string bitmask;
    std::cin >> bitmask;
    std::cin.ignore();

    std::function <double (double)> T_t0_values = T_step(2., 3.);
    std::function <double (double)> T_xa_values = T_sin(2., 0.000, 0.);
    std::function <double (double)> T_xb_values = T_sin(1., 0.000, 0.);

    std::cout << "[default: step 2 3] t0_values = ";
    readConditions(T_t0_values);
    std::cout << "[default: sin 2 0 0] xa_values = ";
    readConditions(T_xa_values);
    std::cout << "[default: sin 1 0 0] xb_values = ";
    readConditions(T_xb_values);

    std::cout << "generating images...";

    generate_images(delta_x, delta_t, u, kappa, x_range, t_range, bitmask, T_t0_values, T_xa_values, T_xb_values);
}
