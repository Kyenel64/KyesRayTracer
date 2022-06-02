#include "rt.h"
#include "hittable_list.h"
#include "sphere.h"
#include "color.h"

#include <iostream>
#include <chrono>



color ray_color(const Ray& r, const Hittable& world)
{
    hit_record rec;
    if (world.hit(r, 0, infinity, rec))
    {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0-t) * color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0); //lerp
}

int main() 
{
    // Image propterties
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // World
    Hittable_list world;
    world.add(std::make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(point3(0, -100.5, -1), 100));

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0; // Distance from the eye to plane.

    auto origin = point3(0, 0, 0); // eye location
    auto horizontal = vec3(viewport_width, 0, 0); // offset vector
    auto vertical = vec3(0, viewport_height, 0); // offset vector
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length); // lower left of plane

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = image_height - 1; i >= 0; i--)
    {
        std::cerr << "\rScanlines remaining: " << i << std::flush;
        for (int j = 0; j < image_width; j++)
        {
            auto u = double(j) / (image_width - 1);
            auto v = double (i) / (image_height - 1);
            Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin); // cast rays across plane
            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }

    // calculate time taken to render
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cerr << "\nFinished in: " << duration.count() << " ms" << std::endl;

    return 0;
}