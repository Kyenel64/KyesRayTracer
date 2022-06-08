#include "rt.h"

#include "hittable_list.h"
#include "sphere.h"
#include "color.h"
#include "camera.h"

#include <iostream>
#include <chrono>

point3 cameraPos(0, 0, 0);
auto FOV = 90.0;

// calculate color of pixel
color ray_color(const Ray& r, const Hittable& world, int depth)
{
    hit_record rec;
    if (depth <= 0)
    {
        return color(0, 0, 0);
    }
    if (world.hit(r, 0.001, infinity, rec))
    {
        // create reflecion vector
        point3 target = rec.p + rec.normal + random_unit_vector();
        // Recursively cast reflection rays half the strength.
        return 0.5 * ray_color(Ray(rec.p, target - rec.p), world, depth-1);
    }
    // background color
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0-t) * color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0); //lerp
}

int main() 
{
    // Image propterties
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 1920; //default 400
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 500; // default 100
    const int maxDepth = 10; // default 50

    // World
    Hittable_list world;
    world.add(std::make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(point3(0, -100.5, -1), 100));

    // Camera
    Camera cam;

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = image_height - 1; i >= 0; i--)
    {
        std::cerr << "\rScanlines remaining: " << i << std::flush;
        for (int j = 0; j < image_width; j++)
        {
            color pixel_color;
            // anti aliasing
            for (int s = 0; s < samples_per_pixel; s++)
            {
                auto u = (j + random_double()) / (image_width - 1);
                auto v = (i + random_double()) / (image_height - 1);
                Ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, maxDepth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    // calculate time taken to render
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cerr << "\nFinished in: " << duration.count() / 1000000.0 << "seconds" << std::endl;

    return 0;
}