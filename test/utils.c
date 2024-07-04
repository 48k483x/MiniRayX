#include "miniRT.h"

void put_pixel(t_mlx *mlx, int x, int y, int color)
{
    char *dst;

    dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
    *(unsigned int*)dst = color;
}

int get_color(t_vec3 color)
{
    int r = fmin(255, color.x * 255);
    int g = fmin(255, color.y * 255);
    int b = fmin(255, color.z * 255);
    return (r << 16) | (g << 8) | b;
}

double deg_to_rad(double deg)
{
    return deg * M_PI / 180.0;
}

int handle_keypress(int keycode, Hook_params *params)
{
    t_mlx *mlx = params->mlx;
    t_scene *scene = params->scene;

    if (keycode == ESC_KEY)
    {
        mlx_destroy_window(mlx->mlx, mlx->win);
        exit(0);
    }
    // Add other key handling here if needed

    draw_scene(mlx, scene);
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
    return 0;
}

int handle_close(t_mlx *mlx)
{
    mlx_destroy_window(mlx->mlx, mlx->win);
    exit(0);
    return 0;
}