/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahrou <achahrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:11:26 by aaamam            #+#    #+#             */
/*   Updated: 2024/07/13 10:33:56 by achahrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	error(const char *msg)
{
	write(2, "Error: ", 7);
	write(2, msg, _strlen(msg));
	write(2, "\n", 1);
	return (0);
}

int	free_mlx(t_scene *scene)
{
	mlx_destroy_image(scene->info.vars.mlx, scene->info.vars.img.img);
	mlx_destroy_window(scene->info.vars.mlx, scene->info.vars.win);
	mlx_destroy_display(scene->info.vars.mlx);
	free(scene->info.vars.mlx);
	return (0);
}

void	free_obj(t_objs *obj)
{
	t_objs	*tmp;

	while (obj)
	{
		tmp = obj->next;
		free(obj);
		obj = tmp;
	}
}

int	main(int ac, char **av)
{
	t_scene	scene;
	char	**sc;

	scene = (t_scene){0};
	if (ac != 2 || !_check_extension(av[1]))
		return (error("Invalid arguments"));
	sc = get_scene(av[1]);
	if (!sc || !alc_num(sc))
		return (em_free("Invalid scene file", sc, NULL, NULL));
	if (!selecte(&scene, sc))
		return (em_free("Invalid scene file", sc, NULL, NULL));
	if (!(select_2(&scene, sc)))
	{
		free_obj(scene.objs);
		return (em_free("Invalid scene file", sc, NULL, NULL));
	}
	ft_render(&scene);
	free_obj(scene.objs);
	free_mlx(&scene);
	free_tab(sc);
	return (0);
}
