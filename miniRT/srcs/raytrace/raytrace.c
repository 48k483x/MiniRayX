#include "../include/miniRT.h"

void    my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
    char    *dst;

    dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
    *(unsigned int *)dst = color;
}

void    ft_draw(t_scene *scene, t_mlx *mlx, t_render *render)
{
    render->scale = tan(scene->cam.fov * 0.5 * M_PI / 180.0);
    render->x = -1;
    while (++render->x < WIDTH)
    {
        render->y = -1;
        while (++render->y < HEIGHT)
        {
            render->px = 2 * ((double)render->x + 0.5) / ((double)WIDTH - 1)* render->cam.aspratio * render->scale;
            render->py = 1 - 2 * ((double)render->y + 0.5) / ((double)HEIGHT - 1) * render->scale;
            render->ray = set_ray(&render->cam, render->px, render->py);
            render->color = ray_color(scene, &render->ray);
            my_mlx_pixel_put(mlx, render->x, render->y, 0x00FF0000);
        }
    }
}

void    initialize_window(t_mlx *mlx)
{
    mlx->mlx = mlx_init();
    mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "miniRT");
    mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
    mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_len, &mlx->endian);
}

void    ft_render(t_scene *scene, t_mlx *mlx)
{
    t_render render;

    render.cam = set_camera(scene);
    initialize_window(mlx);
    ft_draw(scene, mlx, &render);
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
    mlx_hook(mlx->win, 2, 1L << 0, esc_key, mlx);
    mlx_loop(mlx->mlx);
}