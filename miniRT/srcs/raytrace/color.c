#include "../include/miniRT.h"

int is_inside(t_vec3 ray, t_vec3 normal)
{
    return (vec3_dot(ray, normal) > 0);
}

t_vec3  add_coef(t_vec3 col1, t_vec3 col2, float ratio)
{
    t_vec3  ret;

    ret.x = col1.x * (col2.x / 255) * ratio;
    ret.y = col1.y * (col2.y / 255) * ratio;
    ret.z = col1.z * (col2.z / 255) * ratio;
    return (ret);
}

t_vec3  ray_color(t_scene *scene, t_ray *ray, char **sc)
{
    t_inter inter;
    t_vec3  pixel_clr;
    t_vec3  amb;

    inter = intersect(scene, ray, sc);
    // printf("inter.t: %f\n", inter.t);
    if (inter.t > ESP)
    {
        amb = add_coef(inter.color, scene->amb.color, scene->amb.intensity);
        if (is_inside(ray->dir, inter.normal))
            inter.normal = vec3_scale(inter.normal, -1);
        t_light_params params = {
            .point = inter.hit,
            .normal = inter.normal,
            .view_dir = vec3_scale(ray->dir, -1),
            .light = scene->light,
            .object_color = inter.color,
            .spheres = scene->sph,
            .planes = scene->pla,
            .cylinders = scene->cyl,
        };
        printf("object color: %f %f %f\n", inter.color.x, inter.color.y, inter.color.z);
        pixel_clr = calculate_light(params);
        printf("pixel color: %f %f %f\n", pixel_clr.x, pixel_clr.y, pixel_clr.z);
        return (pixel_clr);
    }
    return((t_vec3){0, 0, 0});
}
