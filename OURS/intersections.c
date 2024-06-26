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

int ray_intersect_cylinder(Ray ray, Cylinder cyl, float *t)
{
    Vec3 oc = vec3_sub(ray.origin, cyl.center);
    Vec3 axis_normalized = vec3_normalize(cyl.axis);
    
    float a = vec3_dot(ray.direction, ray.direction) - 
              pow(vec3_dot(ray.direction, axis_normalized), 2);
    float b = 2 * (vec3_dot(ray.direction, oc) - 
              vec3_dot(ray.direction, axis_normalized) * vec3_dot(oc, axis_normalized));
    float c = vec3_dot(oc, oc) - 
              pow(vec3_dot(oc, axis_normalized), 2) - cyl.radius * cyl.radius;

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) return 0;

    float t0 = (-b - sqrt(discriminant)) / (2 * a);
    float t1 = (-b + sqrt(discriminant)) / (2 * a);

    if (t0 > t1)
    {
        float temp = t0;
        t0 = t1;
        t1 = temp;
    }

    float y0 = vec3_dot(vec3_add(ray.origin, vec3_scale(ray.direction, t0)), axis_normalized);
    float y1 = vec3_dot(vec3_add(ray.origin, vec3_scale(ray.direction, t1)), axis_normalized);

    if (y0 < 0)
    {
        if (y1 < 0) return 0;
        t0 = t0 + (t1 - t0) * (y0 / (y0 - y1));
        y0 = 0;
    }
    if (y0 > cyl.height)
    {
        if (y1 > cyl.height) return 0;
        t0 = t0 + (t1 - t0) * ((y0 - cyl.height) / (y0 - y1));
        y0 = cyl.height;
    }

    *t = t0;
    return 1;
}