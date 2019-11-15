#include "implicit_backward_flow.h"

#include "common_implicit.h"
#include "method_utils.h"
#include <cassert>

std::vector <std::vector <double> >  // T[x][t]
implicit_backward_flow
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
{
    double r = calc_r(u, cappa, delta_x, delta_t);
    double s = calc_s(u, cappa, delta_x, delta_t);

    return common_implicit
    (
        x_size, 
        t_size, 
        T_t0_values,
        T_xa_values,
        T_xb_values,
        (s + r),
        r
    );
}
