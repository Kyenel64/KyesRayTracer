#include "vec3.h"
#include "ray.h"
#include "color.h"

#include <iostream>

color ray_color(const Ray& r)
{
    vec3 unit_direction = unit_vector(r.direction());  // normalize direction
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0-t) * color(1.0, 1.0, 1.0) + t*color(1.0, 0.4, 1.0); //lerp
}

int main() 
{
    // Image propterties
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

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

    for (int i = image_height - 1; i >= 0; i--)
    {
        std::cerr << "\rScanlines remaining: " << i << std::flush;
        for (int j = 0; j < image_width; j++)
        {
            auto u = double(j) / (image_width - 1);
            auto v = double (i) / (image_height - 1);
            Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin); // cast rays across plane
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone." << std::endl;
    return 0;
}