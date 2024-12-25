/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahrou <achahrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:26:56 by achahrou          #+#    #+#             */
/*   Updated: 2024/07/13 09:53:22 by achahrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

int	handle_key(int key, t_scene *sc)
{
	if (key == 65307)
	{
		sc->exit = 1;
		return (1);
	}
	return (0);
}

int	check_exit(t_scene *sc)
{
	if (sc->exit == 1)
	{
		mlx_loop_end(sc->info.vars.mlx);
		return (1);
	}
	return (0);
}

int	red_button(t_scene *sc)
{
	sc->exit = 1;
	return (0);
}
