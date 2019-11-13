#include "explicit_backward_flow.h"

#include <cassert>

std::vector <std::vector <double> >  // T[x][t]
explicit_backward_flow
(
    double delta_x,
    double delta_t,
    double u,
    double cappa,
    std::pair <double, double> x_range, 
    std::pair <double, double> t_range, 
    std::vector <double> const & T_t0_values,
    std::vector <double> const & T_xa_values,
    std::vector <double> const & T_xb_values
)
{
    size_t x_size = (delta_x + x_range.second - x_range.first) / delta_x;
    size_t t_size = (delta_t + t_range.second - t_range.first) / delta_t;

    assert(x_size > 4);
    assert(t_size > 1);

    double r = cappa * delta_t / (delta_x * delta_x);
    double s = u * delta_t / delta_x;

    std::vector <std::vector <double> > answer(x_size, std::vector <double> (t_size));
    for (size_t i = 0; i != x_size; ++i)
    {
        answer[i][0] = T_t0_values[i];
    }

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
