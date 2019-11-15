#ifndef COMMON_IMPLICIT_H
#define COMMON_IMPLICIT_H

#include <vector>

std::vector <std::vector <double> >  // T[x][t]
common_implicit
(
    size_t x_size, 
    size_t t_size, 
    std::vector <double> const & T_t0_values,
    std::vector <double> const & T_xa_values,
    std::vector <double> const & T_xb_values,
    double first,
    double second
);

#endif
