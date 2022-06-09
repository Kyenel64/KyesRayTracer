#include "rt.h"

#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

#include <iostream>
#include <chrono>


void write_color(std::ostream &out, color pixel_color, int samples_per_pixel)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide color by number of samples. Gamma correct.
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // Print translated [0, 255] value of each color
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << std::endl;
}

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
        // Material colors
        Ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);
        return color(0, 0, 0);
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
    const int image_width = 400; //default 400
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100; // default 100
    const int maxDepth = 10; // default 50

    // World
    Hittable_list world;

    auto material_ground = std::make_shared<Lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(color(0.7, 0.3, 0.3));
    auto material_left   = std::make_shared<Metal>(color(0.8, 0.8, 0.8));
    auto material_right  = std::make_shared<Metal>(color(0.8, 0.6, 0.2));

    world.add(std::make_shared<Sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<Sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(std::make_shared<Sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(std::make_shared<Sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));
    
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