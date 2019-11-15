#include "start_parameters.h"

#include <math.h>

T_sin::T_sin (double _a, double _b, double _c) noexcept :
    a(_a),
    b(_b),
    c(_c)
{}

double T_sin :: operator () (double x) noexcept
{
    return a * std::sin(b * x) + c;
}

T_step::T_step(double _a, double _b) noexcept :
    a(_a),
    b(_b)
{}

double T_step ::operator() (double x) noexcept
{
    if (x <= a) return 1.;
    if (x >= b) return 0.;
    return x / (b - a) + b / (b - a);
}
