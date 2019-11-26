#pragma once
#include <utility>
#include <functional>

void generate_images
(
    double delta_x,
    double delta_t,
    double u,
    double kappa,
    std::pair <double, double> x_range,
    std::pair <double, double> t_range,
    std::string bitmask,
    std::function <double (double)> const& T_t0_values,
    std::function <double (double)> const& T_xa_values,
    std::function <double (double)> const& T_xb_values
);