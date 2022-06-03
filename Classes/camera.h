#ifndef CAMERA_H
#define CAMERA_H

#include "rt.h"

class Camera
{
public:
    Camera(point3 cameraPos, double focalLength, double aspectRatio) : origin(cameraPos)
    {
        auto aspect_ratio = aspectRatio;
        auto viewport_height = 2.0;
        auto viewport_width = aspect_ratio * viewport_height;
        auto focal_length = focalLength / 100.0;

        horizontal = vec3(viewport_width, 0.0, 0.0);
        vertical = vec3(0.0, viewport_height, 0.0);
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);
    }

    Ray get_ray(double u, double v) const
    {
        return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    }

private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};

#endif