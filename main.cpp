#include <iostream>
#include "methods/cheharda.h"
#include "methods/implicit_forward_flow.h"
#include "methods/implicit_backward_flow.h"
#include "methods/explicit_forward_flow.h"
#include "methods/explicit_backward_flow.h"
#include "methods/method_utils.h"
#include "plots/images_generator.h"

int main ()
{
    double delta_x, delta_t, u, kappa;
    std::pair<double, double> x_range, t_range;
    std::cout << "delta_x = ";
    std::cin >> delta_x;
    std::cout << "delta_t = ";
    std::cin >> delta_t;
    std::cout << "u = ";
    std::cin >> u;
    std::cout << "kappa = ";
    std::cin >> kappa;
    std::cout << "[space separated] x_range = ";
    std::cin >> x_range.first >> x_range.second;
    t_range.first = 0;
    std::cout << "simulation_time = ";
    std::cin >> t_range.second;
    std::cout << std::endl;
    std::cout << "r = " << calc_r(u, kappa, delta_x, delta_t) << std::endl;
    std::cout << "s = " << calc_s(u, kappa, delta_x, delta_t) << std::endl;
    generate_images(delta_x, delta_t, u, kappa, x_range, t_range);
}
