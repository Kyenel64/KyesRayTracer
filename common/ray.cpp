#include "ray.h"

Ray::Ray() {}

Ray::Ray(const point3 &origin, const vec3 &direction) : orig(origin), dir(direction) {}

point3 Ray::origin() const
{
    return orig;
}

vec3 Ray::direction() const
{
    return dir;
}

point3 Ray::at(double t) const
{
    return orig + t*dir;
}