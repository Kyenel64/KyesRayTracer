#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "rt.h"

class Sphere : public Hittable
{
public:
    Sphere() {}
    Sphere(point3 cen, double r, std::shared_ptr<Material> m) : center(cen), radius(r), mat_ptr(m) {}

    // Detect if ray hits sphere.
    virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;
public:
    point3 center;
    double radius;
    std::shared_ptr<Material> mat_ptr;
};

#endif