#include "miniRT.h"



void ft_draw(t_scene *sc, t_render *render, t_mlx *mlx)
{
    float scale = tan((sc->cam.fov * 0.5) * M_PI / 180);
    float aspect_ratio = (float)WIDTH / (float)HEIGHT;

    render->y = HEIGHT - 1;
    while (render->y >= 0)
    {
        render->x = WIDTH - 1;
        while (render->x >= 0)
        {
            render->u = (2 * ((float)render->x + 0.5) / WIDTH - 1) * render->cam.aspect_r * scale;
            render->v = (1 - 2 * ((float)render->y + 0.5) / HEIGHT) * scale;
            render->ray = ray_primary(&render->cam, render->u, render->v);
            render->ray_col = ray_color(sc, &render->ray);
            my_mlx_put_pixel(mlx, render->x, HEIGHT -1 - render->y, get_color(render->ray_col));

            render->x--;
        }
        render->y--;
    }
}


void	image_init(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "miniRT");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_len, &mlx->endian);
}

void    ft_render(t_scene *sc)
{
	t_render	render;
	t_mlx		mlx;

	render.cam = set_camera(sc);
	image_init(&mlx);
	ft_draw(sc, &render, &mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.mlx);
}