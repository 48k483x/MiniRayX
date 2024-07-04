#include "miniRT.h"

int is_in_shadow(t_ray shadow_ray, t_scene *scene, double light_distance)
{
    t_inter inter;

    for (t_sph_l *sph = scene->sph; sph != NULL; sph = sph->next)
    {
        if (ray_intersect_sphere(shadow_ray, sph->sph, &inter) && inter.t > 0.001 && inter.t < light_distance)
            return 1;
    }

    for (t_pla_l *pla = scene->pla; pla != NULL; pla = pla->next)
    {
        if (ray_intersect_plane(shadow_ray, pla->pla, &inter) && inter.t > 0.001 && inter.t < light_distance)
            return 1;
    }

    for (t_cyl_l *cyl = scene->cyl; cyl != NULL; cyl = cyl->next)
    {
        if (ray_intersect_cylinder(shadow_ray, cyl->cyl, &inter) && inter.t > 0.001 && inter.t < light_distance)
            return 1;
    }

    return 0;
}

t_vec3 calculate_lighting(t_light_params *params)
{
    t_vec3 normal = vec3_normalize(params->normal);
    t_vec3 view_dir = vec3_normalize(params->view_dir);

    t_vec3 light_dir = vec3_sub(params->light.origin, params->point);
    double light_distance = vec3_length(light_dir);
    light_dir = vec3_normalize(light_dir);

    // Ambient
    t_vec3 ambient = vec3_scale(params->object_color, params->scene->amb.intensity);

    // Check for shadows
    t_ray shadow_ray = {params->point, light_dir};
    if (is_in_shadow(shadow_ray, params->scene, light_distance))
    {
        return ambient;
    }

    // Diffuse
    double diff = fmax(vec3_dot(normal, light_dir), 0.0);
    t_vec3 diffuse = vec3_scale(vec3_multiply(params->object_color, params->light.color), diff * params->light.intensity);

    // Specular
    double specular_strength = 0.5;
    t_vec3 reflect_dir = vec3_sub(vec3_scale(normal, 2.0 * vec3_dot(light_dir, normal)), light_dir);
    double spec = pow(fmax(vec3_dot(view_dir, reflect_dir), 0.0), 32);
    t_vec3 specular = vec3_scale(params->light.color, specular_strength * spec * params->light.intensity);

    // Combine
    t_vec3 result = vec3_add(vec3_add(ambient, diffuse), specular);

    // Clamp values
    result.x = fmin(result.x, 1.0);
    result.y = fmin(result.y, 1.0);
    result.z = fmin(result.z, 1.0);

    return result;
}