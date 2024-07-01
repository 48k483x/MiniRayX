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
    // printf("a: %f, b: %f, c: %f\n", sphere.a, sphere.b, sphere.c);
    sphere.t = sphere.b * sphere.b - 4 * sphere.a * sphere.c;
    // printf("t: %f\n", sphere.t);
    if (sphere.t < 0)
        return (-1);
    sphere.t1 = (-sphere.b - sqrt(sphere.t)) / (2 * sphere.a);
    sphere.t2 = (-sphere.b + sqrt(sphere.t)) / (2 * sphere.a);
    // printf("t1: %f, t2: %f\n", sphere.t1, sphere.t2);
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


double inter_plane(t_ray *ray, t_pla *pla) {
    double denom = vec3_dot(pla->normal, ray->dir);
    
    if (fabs(denom) > ESP) { // Ensure the ray is not parallel to the plane
        t_vec3 p0l0 = vec3_sub(pla->origin, ray->origin);
        double t = vec3_dot(p0l0, pla->normal) / denom;
        if (t >= ESP) {
            return t; // Intersection is in front of the ray origin
        }
    }
    return -1.0; // No intersection or intersection is behind the ray origin
}

