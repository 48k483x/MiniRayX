/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: void_id <void_id@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:37:25 by smia              #+#    #+#             */
/*   Updated: 2024/06/25 12:40:48 by void_id          ###   ########.fr       */
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

int	handle_key(int key, t_vars *vars)
{
	if (key == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int	red_button(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}
