/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahrou <achahrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:27:00 by achahrou          #+#    #+#             */
/*   Updated: 2024/07/13 10:48:25 by achahrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_draw(t_render info, t_scene *sc)
{
	info.y = HEIGHT - 1;
	while (info.y >= 0)
	{
		info.x = 0;
		while (info.x < WIDTH)
		{
			info.v = ((double)info.x * 2 / WIDTH - 1) * info.cam.aspect_r;
			info.u = ((double)info.y * 2 / HEIGHT - 1) / info.cam.aspect_r;
			info.ray_ = ray_primary(&info.cam, info.v, info.u);
			info.ray_col = ray_color(&info.ray_, sc);
			my_mlx_pixel_put(&info.img, info.x, HEIGHT - 1 - info.y,
				create_rgb(info.ray_col.x, info.ray_col.y, info.ray_col.z));
			info.x++;
		}
		info.y--;
	}
}

void	image_init(t_render	*info)
{
	info->vars.mlx = mlx_init();
	info->vars.win = mlx_new_window(info->vars.mlx, WIDTH, HEIGHT, "MiniRT");
	info->img.img = mlx_new_image(info->vars.mlx, WIDTH, HEIGHT);
	info->img.addr = mlx_get_data_addr(info->img.img, &info->img.bits_per_pixel,
			&info->img.line_length, &info->img.endian);
	info->vars.img = info->img;
}

void	ft_render(t_scene *sc)
{
	sc->exit = 0;
	sc->info = (t_render){0};
	sc->info.cam = set_camera(sc);
	image_init(&sc->info);
	ft_draw(sc->info, sc);
	mlx_put_image_to_window(sc->info.vars.mlx, sc->info.vars.win, \
									sc->info.img.img, 0, 0);
	mlx_hook(sc->info.vars.win, 17, 0, red_button, sc);
	mlx_key_hook(sc->info.vars.win, handle_key, sc);
	mlx_loop_hook(sc->info.vars.mlx, check_exit, sc);
	mlx_loop(sc->info.vars.mlx);
}
