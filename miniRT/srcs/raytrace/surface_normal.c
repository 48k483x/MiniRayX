#include "../include/miniRT.h"

t_inter sphere_normal(t_inter hold, t_scene *scene, t_ray *ray)
{
    t_inter inter;

    inter.t = inter_sphere(ray, &scene->sph->sph);
    if ((hold.t > inter.t || hold.t == -1) && inter.t > ESP)
    {
        inter.color = scene->sph->sph.color;
        printf("sphere color: %f %f %f\n", inter.color.x, inter.color.y, inter.color.z);
        inter.hit = vec3_add(ray->origin, vec3_scale(ray->dir, inter.t));
        inter.normal = vec3_normalize(vec3_sub(inter.hit, scene->sph->sph.origin));
        hold = inter;
    }
    return (hold);
}