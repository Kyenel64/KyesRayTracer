#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "rt.h"

class Sphere : public Hittable
{
public:
    Sphere() {}
    Sphere(point3 cen, double r) : center(cen), radius(r) {}

    // Detect if ray hits sphere.
    virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;
public:
    point3 center;
    double radius;
};

#endif