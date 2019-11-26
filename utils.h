#ifndef UTILS_H
#define UTILS_H

#include <functional>
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

typedef 
std::function
<
    std::vector <std::vector <double> > // T[x][t]
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
    )
> 
method_type;

#endif
