#ifndef RT_H
#define RT_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>
#include "ray.h"
#include "vec3.h"

// constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;


// utility functions
double degrees_to_radians(double degrees);
double random_double();
double random_double(double min, double max);
double clamp(double x, double min, double max);

#endif