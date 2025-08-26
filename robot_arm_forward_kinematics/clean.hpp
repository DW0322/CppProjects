#ifndef CLEAN
#define CLEAN

#include <cmath>

const double EPSILON = 1e-10;

double clean(double val)
{
    return std::abs(val) < EPSILON ? 0.0 : val;
}

#endif
