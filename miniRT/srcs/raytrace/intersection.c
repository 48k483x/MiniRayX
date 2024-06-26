#include "../include/miniRT.h"

double inter_sphere(t_ray *ray, t_sph *sph)
{
    t_sphere    sphere;
    double      radius;

    radius = sph->diameter / 2;
    sphere.oc = vec3_sub(ray->origin, sph->origin);
    sphere.a = vec3_dot(ray->dir, ray->dir);
    sphere.b = 2 * vec3_dot(sphere.oc, ray->dir);
    sphere.c = vec3_dot(sphere.oc, sphere.oc) - radius * radius;
    sphere.t = sphere.b * sphere.b - 4 * sphere.a * sphere.c;
    if (sphere.t < 0)
        return (-1);
    sphere.t1 = (-sphere.b - sqrt(sphere.t)) / (2 * sphere.a);
    sphere.t2 = (-sphere.b + sqrt(sphere.t)) / (2 * sphere.a);
    if (sphere.t1 * sphere.t2 > ESP)
    {
        if (sphere.t1 > ESP)
            return (fmin(sphere.t1, sphere.t2));
        return (-1);
    }
    if (sphere.t1 > ESP)
        return (sphere.t1);
    return (sphere.t2);
}

