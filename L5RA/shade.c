#include "miniRT.h"

int shade(t_scene *sc, t_inter inter, t_light *light)
{
    t_vec3  hit_light;
    t_ray   sh_ray;
    t_inter shadow;
    t_vec3  hit_sh;

    hit_light = vec3_sub(light->origin, inter.hit);
    sh_ray.orig = inter.hit;
    sh_ray.dir = vec3_normalize(hit_light);
    shadow = find_inter(sc, &sh_ray);
    hit_sh = vec3_sub(shadow.hit, sh_ray.orig);
    if (shadow.t > EPS && vec3_length(hit_sh) < vec3_length(hit_light))
        return (1);
    return (0);
}

t_vec3  diffuse(t_inter inter, t_light *light, double d)
{
    t_vec3  diff;
    
    diff = add_coef(inter.col, light->color, light->intensity * d);
    return (diff);
}
