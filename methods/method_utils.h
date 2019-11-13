#ifndef METHOD_UTILS_H
#define METHOD_UTILS_H

#include <vector>

template <typename T>
struct quard 
{
    T a, b, c, d;
};

std::vector <double> solve_3_diag (std::vector <quard <double> > const & values);

#endif
