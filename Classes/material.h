#ifndef MATERIAL_H
#define MATERIAL_H

#include "rt.h"

#include "hittable.h"

class Material
{
public:
    virtual bool scatter(const Ray& r_in, const hit_record& rec, color& attenutation, Ray& scattered) const = 0;
};

class Lambertian : public Material
{
public:
    Lambertian(const color& a) : albedo(a) {}

    virtual bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const override
    {
        auto scatter_direction = rec.normal + random_unit_vector();

        //Catch degenerate scatter direction
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered = Ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

public:
    color albedo;
};

class Metal : public Material
{
public:
    Metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    virtual bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const override
    {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = Ray(rec.p, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

public:
    color albedo;
    double fuzz;
};

#endif