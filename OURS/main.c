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

void draw_scene(MLX *mlx, Sphere sphere, Light light, Camera camera)
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
            float t;
            if (ray_intersect_sphere(ray, sphere, &t))
            {
                Vec3 point = vec3_add(ray.origin, vec3_scale(ray.direction, t));
                Vec3 normal = vec3_normalize(vec3_sub(point, sphere.center));
                Vec3 view_dir = vec3_scale(ray.direction, -1);
                Vec3 color = calculate_lighting(point, normal, view_dir, light, sphere);
                put_pixel(mlx, x, y, get_color(color));
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

    if (keycode == 53 || keycode == 65307)
    { // ESC key code for macOS
        mlx_destroy_window(mlx->mlx, mlx->win);
        exit(0);
    }
    else if (keycode == W_KEY)
    { // W key
        camera.pos = vec3_add(camera.pos, vec3_scale(camera.forward, move_speed));
    }
    else if (keycode == S_KEY)
    { // S key
        camera.pos = vec3_add(camera.pos, vec3_scale(camera.forward, -move_speed));
    }
    else if (keycode == A_KEY)
    { // A key
        camera.pos = vec3_add(camera.pos, vec3_scale(camera.right, -move_speed));
    }
    else if (keycode == D_KEY)
    { // D key
        camera.pos = vec3_add(camera.pos, vec3_scale(camera.right, move_speed));
    }
    else if (keycode == UP)
    { // Up arrow key
        camera.pos = vec3_add(camera.pos, vec3_scale(camera.up, move_speed));
    }
    else if (keycode == DOWN)
    { // Down arrow key
        camera.pos = vec3_add(camera.pos, vec3_scale(camera.up, -move_speed));
    }
    else if (keycode == LEFT)
    { // Left arrow key
        camera.forward = vec3_normalize(vec3_add(
            vec3_scale(camera.forward, cos(rotate_speed)),
            vec3_scale(camera.right, -sin(rotate_speed))));
        camera.right = vec3_cross(camera.forward, camera.up);
    }
    else if (keycode == RIGHT)
    { // Right arrow key
        camera.forward = vec3_normalize(vec3_add(
            vec3_scale(camera.forward, cos(rotate_speed)),
            vec3_scale(camera.right, sin(rotate_speed))));
        camera.right = vec3_cross(camera.forward, camera.up);
    }

    draw_scene(mlx, (Sphere){{0, 0, -5}, 1, {1, 0, 0}}, (Light){{5, 5, -5}, {1, 1, 1}, 0.9}, camera);
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
    Light light = {{5, 5, -5}, {1, 1, 1}, 0.9}; // Bright white light

    Camera camera = {
        .pos = {0, 0, 0},
        .forward = {0, 0, -1},
        .up = {0, 1, 0},
        .right = {1, 0, 0}};

    draw_scene(&mlx, sphere, light, camera);

    mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
    mlx_hook(mlx.win, 2, 1L << 0, handle_keypress, &mlx); // Key press event
    mlx_hook(mlx.win, 17, 0, handle_close, &mlx);         // Window close event
    mlx_loop(mlx.mlx);

    return 0;
}
