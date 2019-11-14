#include "start_parameters.h"

#include <math.h>

T_sin::T_sin (double _a, double _b, double _c) :
    a(_a),
    b(_b),
    c(_c)
{}

double T_sin :: operator () (double x)
{
    return a * std::sin(b * x) + c;
}
