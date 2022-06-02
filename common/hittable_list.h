#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

class Hittable_list : public Hittable
{
public:
    Hittable_list() {}
    Hittable_list(std::shared_ptr<Hittable> object);

    void clear();
    void add(std::shared_ptr<Hittable> object);

    virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
    std::vector<std::shared_ptr<Hittable>> objects;
};

#endif