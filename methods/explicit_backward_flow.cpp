#include "explicit_backward_flow.h"

#include "method_utils.h"
#include <cassert>

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
)
{
    assert(x_size > 4);
    assert(t_size > 1);

    double r = calc_r(u, cappa, delta_x, delta_t);
    double s = calc_s(u, cappa, delta_x, delta_t);

    std::vector <std::vector <double> > answer(x_size, std::vector <double> (t_size));
    fill_0_column(answer, T_t0_values);

    for (size_t cur_t = 1; cur_t != t_size; ++cur_t)
    {
        answer[0][cur_t] = T_xa_values[cur_t];
        answer[x_size - 1][cur_t] = T_xb_values[cur_t];

        for (size_t cur_x = 1; cur_x < x_size - 1; ++cur_x)
        {
            answer[cur_x][cur_t] = 
                answer[cur_x][cur_t - 1] * (1. - 2.*r - s) +
                answer[cur_x - 1][cur_t - 1] * (s + r) +
                answer[cur_x + 1][cur_t - 1] * r;
        }
    }

    return answer;
}
