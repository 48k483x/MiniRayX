#include "../include/miniRT.h"

t_inter sphere_normal(t_inter hold, t_scene *scene, t_ray *ray)
{
    t_inter inter;

    inter.t = intersect_sphere(scene->sph->sph, ray);
    if ((hold.t > inter.t || hold.t == -1) && inter.t > ESP)
    {
        inter.color = scene->sph->sph.color;
        inter.hit = vec3_add(ray->origin, vec3_scale(ray->dir, inter.t));
        inter.normal = vec3_normalize(vec3_sub(inter.hit, scene->sph->sph.origin));
        hold = inter;
    }
    return (hold);
}