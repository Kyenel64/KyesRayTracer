#include "hittable_list.h"

// Constructor
Hittable_list::Hittable_list(std::shared_ptr<Hittable> object)
{
    add(object);
}

// Clear list of objects
void Hittable_list::clear()
{
    objects.clear();
}

// Add object to list of objects
void Hittable_list::add(std::shared_ptr<Hittable> object)
{
    objects.push_back(object);
}

// Hit detect with ray for all objects. keep track of closest ray to draw.
bool Hittable_list::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (unsigned int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->hit(r, t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}