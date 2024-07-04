#include "miniRT.h"

int ray_intersect_sphere(t_ray ray, t_sph sphere, t_inter *inter)
{
    t_vec3 oc = vec3_sub(ray.origin, sphere.origin);
    double radius = sphere.diameter / 2.0;
    double a = vec3_dot(ray.dir, ray.dir);
    double b = 2.0 * vec3_dot(oc, ray.dir);
    double c = vec3_dot(oc, oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0)
        return 0;
    
    double t = (-b - sqrt(discriminant)) / (2.0 * a);
    if (t < 0)
    {
        t = (-b + sqrt(discriminant)) / (2.0 * a);
        if (t < 0)
            return 0;
    }
    
    inter->t = t;
    inter->hit = vec3_add(ray.origin, vec3_scale(ray.dir, t));
    inter->normal = vec3_normalize(vec3_sub(inter->hit, sphere.origin));
    inter->color = sphere.color;
    
    return 1;
}

int ray_intersect_plane(t_ray ray, t_pla plane, t_inter *inter)
{
    double denom = vec3_dot(plane.normal, ray.dir);
    if (fabs(denom) > 1e-6)
    {
        t_vec3 p0l0 = vec3_sub(plane.origin, ray.origin);
        double t = vec3_dot(p0l0, plane.normal) / denom;
        if (t >= 0)
        {
            inter->t = t;
            inter->hit = vec3_add(ray.origin, vec3_scale(ray.dir, t));
            inter->normal = plane.normal;
            inter->color = plane.color;
            return 1;
        }
    }
    return 0;
}

int ray_intersect_cylinder(t_ray ray, t_cyl cylinder, t_inter *inter)
{
    t_vec3 oc = vec3_sub(ray.origin, cylinder.origin);
    t_vec3 axis = vec3_normalize(cylinder.normal);
    double radius = cylinder.diameter / 2.0;
    
    double a = vec3_dot(ray.dir, ray.dir) - pow(vec3_dot(ray.dir, axis), 2);
    double b = 2 * (vec3_dot(ray.dir, oc) - vec3_dot(ray.dir, axis) * vec3_dot(oc, axis));
    double c = vec3_dot(oc, oc) - pow(vec3_dot(oc, axis), 2) - radius * radius;
    
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return 0;
    
    double t1 = (-b - sqrt(discriminant)) / (2 * a);
    double t2 = (-b + sqrt(discriminant)) / (2 * a);
    
    double t;
    if (t1 > t2)
    {
        double temp = t1;
        t1 = t2;
        t2 = temp;
    }
    
    t_vec3 p1 = vec3_add(ray.origin, vec3_scale(ray.dir, t1));
    t_vec3 p2 = vec3_add(ray.origin, vec3_scale(ray.dir, t2));
    
    double h1 = vec3_dot(vec3_sub(p1, cylinder.origin), axis);
    double h2 = vec3_dot(vec3_sub(p2, cylinder.origin), axis);
    
    if (h1 >= 0 && h1 <= cylinder.height)
        t = t1;
    else if (h2 >= 0 && h2 <= cylinder.height)
        t = t2;
    else
        return 0;
    
    inter->t = t;
    inter->hit = vec3_add(ray.origin, vec3_scale(ray.dir, t));
    
    t_vec3 cp = vec3_sub(inter->hit, cylinder.origin);
    t_vec3 proj = vec3_scale(axis, vec3_dot(cp, axis));
    inter->normal = vec3_normalize(vec3_sub(cp, proj));
    
    inter->color = cylinder.color;
    
    return 1;
}