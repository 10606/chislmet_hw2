#include "cheharda.h"

#include "implicit_backward_flow.h"
#include <cassert>

std::vector <std::vector <double> >  // T[x][t]
cheharda
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
    assert(t_size > 2);

    std::vector <std::vector <double> > answer(x_size, std::vector <double> (t_size));
    for (size_t i = 0; i != x_size; ++i)
    {
        answer[i][0] = T_t0_values[i];
    }

    std::vector <std::vector <double> > start_values = 
        implicit_backward_flow
        (
            delta_x,
            delta_t,
            u, 
            cappa,
            x_range,
            {t_range.first, t_range.first + 2 * delta_t}, 
            T_t0_values,
            T_xa_values,
            T_xb_values
        );

    for (size_t cur_x = 0; cur_x != x_size; ++cur_x)
    {
        answer[cur_x][1] = start_values[cur_x][1];   
    }

    for (size_t cur_t = 2; cur_t != t_size; ++cur_t)
    {
        for (size_t cur_x = 1; cur_x != x_size - 1; ++cur_x)
        {
            answer[cur_x][cur_t] = 
                answer[cur_x + 1][cur_t - 1] * (-u * delta_t / delta_x) +
                answer[cur_x][cur_t - 2] +
                answer[cur_x - 1][cur_t - 1] * ( u * delta_t / delta_x);
        }
    }

    return answer;
}
