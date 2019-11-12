#ifndef IMPLICIT_FORWARD_FLOW_H
#define IMPLICIT_FORWARD_FLOW_H

#include <vector>

std::vector <std::vector <double> >  // T[x][t]
implicit_forward_flow
(
    double delta_x,
    double delta_t,
    double u,
    double cappa,
    std::pair <double, double> x_range, 
    std::pair <double, double> t_range, 
    std::vector <double> T_t0_values
)
{
    size_t x_size = (delta_x + x_range.second - x_range.first) / delta_x;
    size_t t_size = (delta_t + t_range.second - t_range.first) / delta_t;

    std::vector <std::vector <double> > answer(x_size, std::vector <double> (t_size));
    for (size_t i = 0; i != x_size; ++i)
    {
        answer[i][0] = T_t0_values[i];
    }

    for (size_t cur_t = 1; cur_t != t_size; ++cur_t)
    {
        double t = static_cast <double> (cur_t) * delta_t + t_range.first;
        
        answer[0][cur_t] = 0.; //TODO
        answer[1][cur_t] = 0.; //TODO
        
        for (size_t cur_x = 2; cur_x != x_size; ++cur_x)
        {
            double x = static_cast <double> (cur_x) * delta_x + x_range.first;
        
            answer[cur_x][cur_t] =  
                answer[cur_x - 1][cur_t] * 
                    (delta_x * delta_x / cappa / delta_t + delta_x * u / cappa + 2.) 
                - 
                answer[cur_x - 2][cur_t] * 
                    (delta_x * u / cappa + 1.)
                -
                answer[cur_x - 1][cur_t - 1] * 
                    (delta_x * delta_x / cappa / delta_t);
        }
    }
    
    return answer;
}

#endif
