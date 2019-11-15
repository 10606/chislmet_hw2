#include "common_implicit.h"

#include "method_utils.h"
#include <cassert>

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
)
{
    assert(x_size > 5);
    assert(t_size > 1);

    std::vector <std::vector <double> > answer(x_size, std::vector <double> (t_size));
    fill_0_column(answer, T_t0_values);

    for (size_t cur_t = 1; cur_t != t_size; ++cur_t)
    {
        answer[0][cur_t]          = T_xa_values[cur_t];
        answer[x_size - 1][cur_t] = T_xb_values[cur_t];
        
        std::vector <quard <double> > system_ur(x_size - 2);
        system_ur.front() = {0,  (1 + first + second), -(second), (answer[1][cur_t - 1] + first * answer[0][cur_t])};
        system_ur.back()  = {-first, (1 + first + second), 0,        (answer[x_size - 2][cur_t - 1] + (second) * answer[x_size - 1][cur_t])};

        for (size_t cur_x = 1; cur_x != system_ur.size() - 1; ++cur_x)
        {
            system_ur[cur_x] = {-first, (1. + first + second), -(second), answer[cur_x + 1][cur_t - 1]};
        }
        
        std::vector <double> cur_x_values = solve_3_diag(system_ur);

        for (size_t cur_x = 0; cur_x != system_ur.size(); ++cur_x)
        {
            answer[cur_x + 1][cur_t] = cur_x_values[cur_x];
        }
    }
    
    return answer;
}

