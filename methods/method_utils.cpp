#include "method_utils.h"

std::vector <double> solve_3_diag (std::vector <quard <double> > const & values)
{
    if (values.empty())
    {
        return {};
    }
    if (values.size() == 1)
    {
        return {values[0].d / values[0].b};
    }
    
    std::vector <std::pair <double, double> > a_b = 
    {{
        -values[0].c / values[0].b, 
        values[0].d / values[0].b
    }};

    for (size_t i = 1; i != values.size() - 1; ++i)
    {
        double alpha = -values[i].c / 
            (values[i].a * a_b[i - 1].first + values[i].b);

        double beta = (values[i].d - values[i].a * a_b[i - 1].second) / 
            (values[i].a * a_b[i - 1].first + values[i].b);

        a_b.push_back
        ({
            alpha,
            beta
        });
    }

    std::vector <double> answer(values.size());
    
    answer.back() = (values.back().d - values.back().a * a_b.back().second) / 
        (values.back().a * a_b.back().first + values.back().b);

    for (size_t i = values.size() - 2; i < values.size(); --i)
    {
        answer[i] = a_b[i].first * answer[i + 1] + a_b[i].second;
    }

    return answer;
}
