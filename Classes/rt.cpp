#include "rt.h"

double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

double random_double()
{
    // Returns random real in 0,1
    return rand() / (RAND_MAX + 1.0);
}

double random_double(double min, double max)
{
    return min + (max-min) * random_double();
}

double clamp(double x, double min, double max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}