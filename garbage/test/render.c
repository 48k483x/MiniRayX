#include "miniRT.h"

void init_camera(t_camera *cam, t_cam *scene_cam)
{
    cam->origin = scene_cam->origin;
    cam->forward = vec3_normalize(scene_cam->normal);
    cam->up = (t_vec3){0, 1, 0};
    cam->right = vec3_normalize(vec3_cross(cam->forward, cam->up));
    cam->up = vec3_cross(cam->right, cam->forward);
}

t_vec3 ray_color(t_ray *ray, t_scene *scene)
{
    t_inter closest_inter = {INFINITY, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    t_inter current_inter;
    int hit_object = 0;

    // Check sphere intersections
    for (t_sph_l *sph = scene->sph; sph != NULL; sph = sph->next)
    {
        if (ray_intersect_sphere(*ray, sph->sph, &current_inter))
        {
            if (current_inter.t < closest_inter.t)
            {
                closest_inter = current_inter;
                hit_object = 1;
                printf("Sphere hit at (%.2f, %.2f, %.2f), t = %.2f\n", 
                       current_inter.hit.x, current_inter.hit.y, current_inter.hit.z, current_inter.t);
            }
        }
    }

    // Check plane intersections
    for (t_pla_l *pla = scene->pla; pla != NULL; pla = pla->next)
    {
        if (ray_intersect_plane(*ray, pla->pla, &current_inter))
        {
            if (current_inter.t < closest_inter.t)
            {
                closest_inter = current_inter;
                hit_object = 1;
                printf("Plane hit at (%.2f, %.2f, %.2f), t = %.2f\n", 
                       current_inter.hit.x, current_inter.hit.y, current_inter.hit.z, current_inter.t);
            }
        }
    }

    // Check cylinder intersections
    for (t_cyl_l *cyl = scene->cyl; cyl != NULL; cyl = cyl->next)
    {
        if (ray_intersect_cylinder(*ray, cyl->cyl, &current_inter))
        {
            if (current_inter.t < closest_inter.t)
            {
                closest_inter = current_inter;
                hit_object = 1;
                printf("Cylinder hit at (%.2f, %.2f, %.2f), t = %.2f\n", 
                       current_inter.hit.x, current_inter.hit.y, current_inter.hit.z, current_inter.t);
            }
        }
    }

    if (hit_object)
    {
        t_light_params params = {
            closest_inter.hit,
            closest_inter.normal,
            vec3_scale(ray->dir, -1),
            closest_inter.color,
            scene->light,
            scene
        };
        t_vec3 color = calculate_lighting(&params);
        printf("Final color for hit: (%.2f, %.2f, %.2f)\n", color.x, color.y, color.z);
        return color;
    }

    // Background color (dark blue)
    return (t_vec3){0.1, 0.1, 0.3};
}
void draw_scene(t_mlx *mlx, t_scene *scene)
{
    t_render render;
    init_camera(&render.cam, &scene->cam);

    render.scale = tan(deg_to_rad(scene->cam.fov * 0.5));
    render.cam.aspratio = (double)mlx->width / (double)mlx->height;

    printf("Drawing scene...\n");
    printf("Sphere: pos(%.2f, %.2f, %.2f), diameter: %.2f\n", 
           scene->sph->sph.origin.x, scene->sph->sph.origin.y, scene->sph->sph.origin.z, 
           scene->sph->sph.diameter);
    printf("Light: pos(%.2f, %.2f, %.2f), intensity: %.2f\n", 
           scene->light.origin.x, scene->light.origin.y, scene->light.origin.z, 
           scene->light.intensity);

    for (render.y = 0; render.y < mlx->height; ++render.y)
    {
        for (render.x = 0; render.x < mlx->width; ++render.x)
        {
            render.px = (2 * ((render.x + 0.5) / mlx->width) - 1) * render.cam.aspratio * render.scale;
            render.py = (1 - 2 * ((render.y + 0.5) / mlx->height)) * render.scale;

            render.ray.origin = render.cam.origin;
            render.ray.dir = vec3_normalize((t_vec3){
                render.px * render.cam.right.x + render.py * render.cam.up.x + render.cam.forward.x,
                render.px * render.cam.right.y + render.py * render.cam.up.y + render.cam.forward.y,
                render.px * render.cam.right.z + render.py * render.cam.up.z + render.cam.forward.z
            });

            render.color = ray_color(&render.ray, scene);
            put_pixel(mlx, render.x, render.y, get_color(render.color));
        }
    }
    printf("Scene drawing completed.\n");
}