#include "miniRT.h"

// Global camera definition
Camera camera = {
    .pos = {0, 0, 15},
    .forward = {0, 0, 1},
    .up = {0, 1, 0},
    .right = {1, 0, 0}
};

void put_pixel(MLX *mlx, int x, int y, int color)
{
    int index = (x * mlx->bpp / 8) + (y * mlx->size_line);
    mlx->data[index] = color;
    mlx->data[index + 1] = color >> 8;
    mlx->data[index + 2] = color >> 16;
}

int get_color(Vec3 color)
{
    int r = fmin(255, color.x * 255);
    int g = fmin(255, color.y * 255);
    int b = fmin(255, color.z * 255);
    return (r << 16) | (g << 8) | b;
}

void draw_scene(MLX *mlx, Sphere sphere, Plane plane1, Plane plane2, Light light, Camera camera, float ambient_intensity, Vec3 ambient_color)
{
    float aspect_ratio = (float)mlx->width / (float)mlx->height;
    float scale = tan(FOV * 0.5 * M_PI / 180);

    for (int y = 0; y < mlx->height; ++y)
    {
        for (int x = 0; x < mlx->width; ++x)
        {
            float px = (2 * (x + 0.5) / (float)mlx->width - 1) * aspect_ratio * scale;
            float py = (1 - 2 * (y + 0.5) / (float)mlx->height) * scale;

            Vec3 ray_dir = vec3_normalize((Vec3){
                px * camera.right.x + py * camera.up.x + camera.forward.x,
                px * camera.right.y + py * camera.up.y + camera.forward.y,
                px * camera.right.z + py * camera.up.z + camera.forward.z});
            Ray ray = {camera.pos, ray_dir};

            float t_sphere, t_plane1, t_plane2;
            int hit_sphere = ray_intersect_sphere(ray, sphere, &t_sphere);
            int hit_plane1 = ray_intersect_plane(ray, plane1, &t_plane1);
            int hit_plane2 = ray_intersect_plane(ray, plane2, &t_plane2);

            if (hit_sphere || hit_plane1 || hit_plane2)
            {
                float t = INFINITY;
                Vec3 color;
                Vec3 normal;
                Vec3 point;

                if (hit_sphere && t_sphere < t)
                {
                    t = t_sphere;
                    color = sphere.color;
                    point = vec3_add(ray.origin, vec3_scale(ray.direction, t));
                    normal = vec3_normalize(vec3_sub(point, sphere.center));
                }
                if (hit_plane1 && t_plane1 < t)
                {
                    t = t_plane1;
                    color = plane1.color;
                    point = vec3_add(ray.origin, vec3_scale(ray.direction, t));
                    normal = plane1.normal;
                }
                if (hit_plane2 && t_plane2 < t)
                {
                    t = t_plane2;
                    color = plane2.color;
                    point = vec3_add(ray.origin, vec3_scale(ray.direction, t));
                    normal = plane2.normal;
                }

                Vec3 view_dir = vec3_scale(ray.direction, -1);
                Vec3 final_color = calculate_lighting(point, normal, view_dir, light, color, sphere, plane1, plane2);
                
                // Apply ambient lighting
                final_color = vec3_add(final_color, vec3_multiply(color, vec3_scale(ambient_color, ambient_intensity)));
                
                put_pixel(mlx, x, y, get_color(final_color));
            }
            else
            {
                put_pixel(mlx, x, y, 0x000000);
            }
        }
    }
}

int handle_keypress(int keycode, Hook_params *params)
{
    MLX *mlx = params->mlx;
    Camera *camera = params->camera;
    Scene *scene = params->scene;

    const float move_speed = 0.5;
    const float rotate_speed = 0.1;

    if (keycode == ESC_KEY)
    {
        mlx_destroy_window(mlx->mlx, mlx->win);
        exit(0);
    }
    else if (keycode == W_KEY)
        camera->pos = vec3_add(camera->pos, vec3_scale(camera->forward, move_speed));
    else if (keycode == S_KEY)
        camera->pos = vec3_add(camera->pos, vec3_scale(camera->forward, -move_speed));
    else if (keycode == A_KEY)
        camera->pos = vec3_add(camera->pos, vec3_scale(camera->right, -move_speed));
    else if (keycode == D_KEY)
        camera->pos = vec3_add(camera->pos, vec3_scale(camera->right, move_speed));
    else if (keycode == UP)
        camera->pos = vec3_add(camera->pos, vec3_scale(camera->up, move_speed));
    else if (keycode == DOWN)
        camera->pos = vec3_add(camera->pos, vec3_scale(camera->up, -move_speed));
    else if (keycode == LEFT)
    {
        camera->forward = vec3_normalize(vec3_add(
            vec3_scale(camera->forward, cos(rotate_speed)),
            vec3_scale(camera->right, -sin(rotate_speed))));
        camera->right = vec3_cross(camera->forward, camera->up);
    }
    else if (keycode == RIGHT)
    {
        camera->forward = vec3_normalize(vec3_add(
            vec3_scale(camera->forward, cos(rotate_speed)),
            vec3_scale(camera->right, sin(rotate_speed))));
        camera->right = vec3_cross(camera->forward, camera->up);
    }

    draw_scene(mlx, scene->sphere, scene->plane1, scene->plane2, scene->light, *camera, scene->ambient_intensity, scene->ambient_color);
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
    return 0;
}

int handle_close(MLX *mlx)
{
    mlx_destroy_window(mlx->mlx, mlx->win);
    exit(0);
    return 0;
}

int main()
{
    MLX mlx;
    mlx.mlx = mlx_init();
    mlx.width = 800;
    mlx.height = 600;
    mlx.win = mlx_new_window(mlx.mlx, mlx.width, mlx.height, "Ray Tracer");
    mlx.img = mlx_new_image(mlx.mlx, mlx.width, mlx.height);
    mlx.data = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.size_line, &mlx.endian);

    Scene scene;

    // Ambient light (A)
    scene.ambient_intensity = 0.2;
    scene.ambient_color = (Vec3){1.0, 1.0, 1.0}; // 255,255,255 normalized to 0-1 range

    // Light (L)
    scene.light = (Light){{-20, 5, 40}, {1, 1, 1}, 0.6};

    // Sphere (sp)
    scene.sphere = (Sphere){{0, 0, 30}, 2.5, {1, 0, 0}}; // radius is 5/2 because the scene uses diameter

    // Planes (pl)
    scene.plane1 = (Plane){{0, -2.5, 0}, {0, 1, 0}, {0, 1, 1}}; // 0,255,255 normalized to 0-1 range
    scene.plane2 = (Plane){{0, 0, 50}, {0, 0, 1}, {0.498, 0.514, 0.737}}; // 127,131,188 normalized to 0-1 range

    draw_scene(&mlx, scene.sphere, scene.plane1, scene.plane2, scene.light, camera, scene.ambient_intensity, scene.ambient_color);

    mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
    
    Hook_params params = {&mlx, &camera, &scene};
    mlx_hook(mlx.win, 2, 1L << 0, (int (*)(int, void *))handle_keypress, &params);
    mlx_hook(mlx.win, 17, 0, handle_close, &mlx); // Window close event
    mlx_loop(mlx.mlx);

    return 0;
}