#ifndef RT_H
#define RT_H

#include <cmath>
#include <limits>
#include <memory>
#include "ray.h"
#include "vec3.h"

// constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;


// utility functions
inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}
// common headers

#endif