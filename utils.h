#ifndef UTILS_H
#define UTILS_H

#include <vector>

/*

d_T/d_t + u * d_T/d_x - e d_2_T/d_2_x  =  0

x in [a, b]
t in [0, tau]


u 
e
a b 
tau
T(0, x)

delta_t 
delta_x

*/

typedef std::vector <std::vector <double> > (* method_type)  // T[x][t]
(
    double delta_x,
    double delta_t,
    double u,
    double cappa,
    std::pair <double, double> x_range, 
    std::pair <double, double> t_range, 
    std::vector <double> T_t0_values,
    std::vector <double> T_xa_values,
    std::vector <double> T_xb_values
);

#endif
