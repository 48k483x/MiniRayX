#include "miniRT.h"

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

void draw_scene(MLX *mlx, Sphere sphere, Plane plane, Cylinder cylinder, Light light, Camera camera)
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

            float t_sphere, t_plane, t_cylinder;
            int hit_sphere = ray_intersect_sphere(ray, sphere, &t_sphere);
            int hit_plane = ray_intersect_plane(ray, plane, &t_plane);
            int hit_cylinder = ray_intersect_cylinder(ray, cylinder, &t_cylinder);

            if (hit_sphere || hit_plane || hit_cylinder)
            {
                float t = INFINITY;
                Vec3 color;
                Vec3 normal;

                if (hit_sphere && t_sphere < t)
                {
                    t = t_sphere;
                    color = sphere.color;
                    Vec3 point = vec3_add(ray.origin, vec3_scale(ray.direction, t));
                    normal = vec3_normalize(vec3_sub(point, sphere.center));
                }
                if (hit_plane && t_plane < t)
                {
                    t = t_plane;
                    color = plane.color;
                    normal = plane.normal;
                }
                if (hit_cylinder && t_cylinder < t)
                {
                    t = t_cylinder;
                    color = cylinder.color;
                    Vec3 point = vec3_add(ray.origin, vec3_scale(ray.direction, t));
                    Vec3 co = vec3_sub(point, cylinder.center);
                    Vec3 projection = vec3_scale(cylinder.axis, vec3_dot(co, cylinder.axis));
                    normal = vec3_normalize(vec3_sub(co, projection));
                }

                Vec3 point = vec3_add(ray.origin, vec3_scale(ray.direction, t));
                Vec3 view_dir = vec3_scale(ray.direction, -1);
                Vec3 final_color = calculate_lighting(point, normal, view_dir, light, color);
                put_pixel(mlx, x, y, get_color(final_color));
            }
            else
            {
                put_pixel(mlx, x, y, 0x000000);
            }
        }
    }
}

int handle_keypress(int keycode, MLX *mlx)
{
    static Camera camera = {
        .pos = {0, 0, 0},
        .forward = {0, 0, -1},
        .up = {0, 1, 0},
        .right = {1, 0, 0}};
    const float move_speed = 0.1;
    const float rotate_speed = 0.1;

    if (keycode == ESC_KEY)
    {
        mlx_destroy_window(mlx->mlx, mlx->win);
        exit(0);
    }
    else if (keycode == W_KEY)
    {
        camera.pos = vec3_add(camera.pos, vec3_scale(camera.forward, move_speed));
    }
    else if (keycode == S_KEY)
    {
        camera.pos = vec3_add(camera.pos, vec3_scale(camera.forward, -move_speed));
    }
    else if (keycode == A_KEY)
    {
        camera.pos = vec3_add(camera.pos, vec3_scale(camera.right, -move_speed));
    }
    else if (keycode == D_KEY)
    {
        camera.pos = vec3_add(camera.pos, vec3_scale(camera.right, move_speed));
    }
    else if (keycode == UP)
    {
        camera.pos = vec3_add(camera.pos, vec3_scale(camera.up, move_speed));
    }
    else if (keycode == DOWN)
    {
        camera.pos = vec3_add(camera.pos, vec3_scale(camera.up, -move_speed));
    }
    else if (keycode == LEFT)
    {
        camera.forward = vec3_normalize(vec3_add(
            vec3_scale(camera.forward, cos(rotate_speed)),
            vec3_scale(camera.right, -sin(rotate_speed))));
        camera.right = vec3_cross(camera.forward, camera.up);
    }
    else if (keycode == RIGHT)
    {
        camera.forward = vec3_normalize(vec3_add(
            vec3_scale(camera.forward, cos(rotate_speed)),
            vec3_scale(camera.right, sin(rotate_speed))));
        camera.right = vec3_cross(camera.forward, camera.up);
    }

    Sphere sphere = {{0, 0, -5}, 1, {1, 0, 0}};
    Plane plane = {{0, -1, 0}, {0, 1, 0}, {0, 1, 0}};
    Cylinder cylinder = {{2, 0, -6}, {0, 1, 0}, 0.5, 2, {0, 0, 1}};
    Light light = {{5, 5, -5}, {1, 1, 1}, 0.9};

    draw_scene(mlx, sphere, plane, cylinder, light, camera);
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

    Sphere sphere = {{0, 0, -5}, 1, {1, 0, 0}}; // Red sphere
    Plane plane = {{0, -1, 0}, {0, 1, 0}, {0, 1, 0}}; // Green plane
    Cylinder cylinder = {{2, 0, -6}, {0, 1, 0}, 0.5, 2, {0, 0, 1}}; // Blue cylinder
    Light light = {{5, 5, -5}, {1, 1, 1}, 0.9}; // Bright white light

    // Adjust camera to look down from above
    Camera camera = {
        .pos = {2, 10, -6},  // Position high above the scene
        .forward = {0, -1, 0},  // Looking straight down
        .up = {0, 0, 1},  // Up vector is now pointing towards positive Z
        .right = {1, 0, 0}  // Right vector remains the same
    };

    draw_scene(&mlx, sphere, plane, cylinder, light, camera);

    mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
    mlx_hook(mlx.win, 2, 1L << 0, handle_keypress, &mlx); // Key press event
    mlx_hook(mlx.win, 17, 0, handle_close, &mlx);         // Window close event
    mlx_loop(mlx.mlx);

    return 0;
}