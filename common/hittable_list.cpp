#include "hittable_list.h"

Hittable_list::Hittable_list(std::shared_ptr<Hittable> object)
{
    add(object);
}

void Hittable_list::clear()
{
    objects.clear();
}

void Hittable_list::add(std::shared_ptr<Hittable> object)
{
    objects.push_back(object);
}

bool Hittable_list::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects)
    {
        if (object->hit(r, t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}