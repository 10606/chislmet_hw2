#ifndef EXPLICIT_BACKWARD_FLOW_H
#define EXPLICIT_BACKWARD_FLOW_H

#include <vector>

std::vector <std::vector <double> >  // T[x][t]
explicit_backward_flow
(
    double delta_x,
    double delta_t,
    double u,
    double cappa,
    size_t x_size, 
    size_t t_size, 
    std::vector <double> const & T_t0_values,
    std::vector <double> const & T_xa_values,
    std::vector <double> const & T_xb_values
);

#endif
