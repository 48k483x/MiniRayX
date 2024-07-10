/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: void_id <void_id@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:26:52 by achahrou          #+#    #+#             */
/*   Updated: 2024/07/10 12:31:39 by void_id          ###   ########.fr       */
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
		return (em_free("Invalid scene file", sc, NULL, NULL));
	ft_render(&scene);
	while (scene.objs)
	{
		free(scene.objs);
		scene.objs = scene.objs->next;
	}
	free_tab(sc);
	return (0);
}
