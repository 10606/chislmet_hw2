#pragma once
#include <utility>

void generate_images
(
    double delta_x,
    double delta_t,
    double u,
    double kappa,
    std::pair <double, double> x_range,
    std::pair <double, double> t_range,
    bool implicit_only
);
