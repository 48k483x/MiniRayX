#include "miniRT.h"

t_camera    set_camera(t_scene *sc)
{
    t_camera    cam;

    cam.orig = sc->cam.origin;
    cam.aspect_r = (double)WIDTH / (double)HEIGHT;
    cam.theta = sc->cam.fov * (M_PI / 180);
    cam.height = tan(cam.theta / 2);
    cam.width = cam.aspect_r * cam.height;
    cam.forward = sc->cam.normal;
    cam.up =vec3_normalize( vec3_cross(cam.forward, (t_vec3){0, 1, 0}));
    cam.right = vec3_normalize(vec3_cross(cam.up, cam.forward));
    return (cam);
}
t_ray ray_primary(t_camera *cam, double x, double y)
{
    t_ray ray;
    t_vec3 dir;

    dir = vec3_normalize((t_vec3){
        x * cam->right.x + y * cam->up.x + cam->forward.x,
        x * cam->right.y + y * cam->up.y + cam->forward.y,
        x * cam->right.z + y * cam->up.z + cam->forward.z
    });
    ray.orig = cam->orig;
    ray.dir = dir;
    return (ray);
}