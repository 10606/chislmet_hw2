#include "start_parameters.h"

#include <math.h>

double T_sin :: operator () (double x)
{
    return a * std::sin(b * x);
}
