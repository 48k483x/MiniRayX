#include "miniRT.h"

int ray_intersect_sphere(Ray ray, Sphere sphere, float *t)
{
    Vec3 oc = vec3_sub(ray.origin, sphere.center);
    float a = vec3_dot(ray.direction, ray.direction);
    float b = 2.0 * vec3_dot(oc, ray.direction);
    float c = vec3_dot(oc, oc) - sphere.radius * sphere.radius;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
    {
        return 0;
    }
    else
    {
        *t = (-b - sqrt(discriminant)) / (2.0 * a);
        return 1;
    }
}

int ray_intersect_plane(Ray ray, Plane plane, float *t)
{
    float denom = vec3_dot(plane.normal, ray.direction);
    if (fabs(denom) > 1e-6)
    {
        Vec3 p0l0 = vec3_sub(plane.point, ray.origin);
        *t = vec3_dot(p0l0, plane.normal) / denom;
        return (*t >= 0);
    }
    return 0;
}
