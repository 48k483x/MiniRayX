#include "../include/miniRT.h"

double inter_sphere(t_ray *ray, t_sph *sph)
{
    t_vec3 oc = vec3_sub(ray->origin, sph->origin);
    double radius = sph->diameter / 2.0;
    
    double a = vec3_dot(ray->dir, ray->dir);
    double b = 2.0 * vec3_dot(oc, ray->dir);
    double c = vec3_dot(oc, oc) - radius * radius;
    
    double discriminant = b * b - 4 * a * c;
    
    printf("Sphere intersection debug:\n");
    printf("Ray origin: (%f, %f, %f)\n", ray->origin.x, ray->origin.y, ray->origin.z);
    printf("Ray direction: (%f, %f, %f)\n", ray->dir.x, ray->dir.y, ray->dir.z);
    printf("Sphere origin: (%f, %f, %f)\n", sph->origin.x, sph->origin.y, sph->origin.z);
    printf("Sphere radius: %f\n", radius);
    printf("oc vector: (%f, %f, %f)\n", oc.x, oc.y, oc.z);
    printf("a: %f, b: %f, c: %f, discriminant: %f\n", a, b, c, discriminant);
    
    if (discriminant < 0)
        return -1;
    
    double t1 = (-b - sqrt(discriminant)) / (2 * a);
    double t2 = (-b + sqrt(discriminant)) / (2 * a);
    
    printf("t1: %f, t2: %f\n", t1, t2);
    
    if (t1 > ESP)
        return t1;
    if (t2 > ESP)
        return t2;
    
    return -1;
}

