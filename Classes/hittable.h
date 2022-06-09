#ifndef HITTABLE_H
#define HITTABLE_H

#include "rt.h"

class Material;

struct hit_record
{
    point3 p; // Point of hit
    vec3 normal; // Normal direction of hit
    std::shared_ptr<Material> mat_ptr; // Material properties
    double t; // t value on ray
    bool front_face;

    // Reflect normal
    inline void set_face_normal(const Ray& r, const vec3& outward_normal)
    {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable
{
public:
    virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif