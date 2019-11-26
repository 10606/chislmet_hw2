#include <iostream>
#include "methods/cheharda.h"
#include "methods/implicit_forward_flow.h"
#include "methods/implicit_backward_flow.h"
#include "methods/explicit_forward_flow.h"
#include "methods/explicit_backward_flow.h"
#include "methods/method_utils.h"
#include "plots/images_generator.h"
#include <string>

int main ()
{
    double delta_x, delta_t, u, kappa, r, s;
    std::pair<double, double> x_range, t_range;
    std::cout << "delta_x = ";
    std::string dx;
    std::getline(std::cin, dx);
    if (dx == "") {
        delta_x = delta_t = 0.1;
        std::cout << "delta_x = 0.1" << std::endl;
        std::cout << "delta_t = 0.1" << std::endl;
    } else {
        delta_x = std::stod(dx);
        std::cout << "delta_t = ";
        std::cin >> delta_t;
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
    std::cout << std::endl;
    
    generate_images(delta_x, delta_t, u, kappa, x_range, t_range, bitmask);
}
