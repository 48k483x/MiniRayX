#include "../include/miniRT.h"

int esc_key(int key, t_mlx *mlx)
{
    if (key == 65307)
    {
        mlx_destroy_window(mlx->mlx, mlx->win);
        exit(0);
    }
    return (0);
}

t_camera    set_camera(t_scene *scene)
{
    t_camera    cam;

    cam.origin = scene->cam.origin;
    cam.aspratio = (double)WIDTH / (double)HEIGHT;
    cam.theeta = scene->cam.fov * M_PI / 180;
    cam.width = tan(cam.theeta / 2);
    cam.height = cam.aspratio * cam.width;
    cam.forward = scene->cam.normal;
    cam.up = vec3_normalize(vec3_cross(cam.forward, (t_vec3){0, 1, 0}));
    cam.right = vec3_normalize(vec3_cross(cam.up, cam.forward));
    return (cam);
}

t_ray   set_ray(t_camera *cam, double x, double y)
{
    t_ray   ray;

    ray.dir = vec3_normalize((t_vec3){
        x * cam->right.x + y * cam->up.x + cam->forward.x,
        x * cam->right.y + y * cam->up.y + cam->forward.y,
        x * cam->right.z + y * cam->up.z + cam->forward.z
    });
    ray.origin = cam->origin;
    return (ray);
}