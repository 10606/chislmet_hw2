#ifndef IMPLICIT_BACKWARD_FLOW_H
#define IMPLICIT_BACKWARD_FLOW_H

#include <vector>

std::vector <std::vector <double> >  // T[x][t]
implicit_backward_flow
(
    double delta_x,
    double delta_t,
    double u,
    double cappa,
    std::pair <double, double> x_range, 
    std::pair <double, double> t_range, 
    std::vector <double> T_t0_values
);

#endif
