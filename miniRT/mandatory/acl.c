/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahrou <achahrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:26:06 by achahrou          #+#    #+#             */
/*   Updated: 2024/07/10 12:27:58 by achahrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	three_check(char **tab)
{
	if (is_digitf(tab[0]) && is_digitf(tab[1]) && is_digitf(tab[2]))
		return (1);
	return (0);
}

int	em_free(char *mess, char **tab, char **tab2, char **tab3)
{
	if (tab)
		free_tab(tab);
	if (tab2)
		free_tab(tab2);
	if (tab3)
		free_tab(tab3);
	if (!mess)
		return (1);
	else
		return (error(mess));
}

int	fill_amb(t_amb *amb, char *line)
{
	char	**tab;
	char	**colors;
	int		color;

	tab = _split(line, ' ');
	if (tab[3])
	{
		return (em_free(ARG_ERR, tab, NULL, NULL));
	}
	if (_strlen(tab[0]) != 1 || tab[0][0] != 'A' || tab[0][1] != '\0')
	{
		return (em_free("Ambiant light must start with 'A'", tab, NULL, NULL));
	}
	colors = _split(tab[2], ',');
	if (!three_check(colors))
		return (em_free(COLOR, tab, colors, NULL));
	color = create_rgb(_atof(colors[0]), _atof(colors[1]), _atof(colors[2]));
	if (color == -1)
		return (em_free(COLOR, tab, colors, NULL));
	if (!is_digitf(tab[1]) || (_atof(tab[1]) < 0 || _atof(tab[1]) > 1))
		return (em_free(INTENSITY, tab, colors, NULL));
	amb->ratio = _atof(tab[1]);
	amb->col = (t_vec){_atof(colors[0]), _atof(colors[1]), _atof(colors[2])};
	return (em_free(NULL, tab, colors, NULL));
}

int	fill_cam(t_cam *cam, char *line)
{
	char	**tab;
	char	**ori;
	char	**nor;

	tab = _split(line, ' ');
	if (tab[4])
		return (em_free(ARG_ERR, tab, NULL, NULL));
	if (_strlen(tab[0]) != 1 || tab[0][0] != 'C' || tab[0][1] != '\0')
		return (em_free("Camera must start with 'C'", tab, NULL, NULL));
	ori = _split(tab[1], ',');
	if (!three_check(ori))
		return (em_free(ORIGIN_ERR, ori, tab, NULL));
	cam->cen = (t_vec){_atof(ori[0]), _atof(ori[1]), _atof(ori[2])};
	nor = _split(tab[2], ',');
	if (!three_check(nor))
		return (em_free(DIR_VECTOR, ori, nor, tab));
	if (_atof(nor[0]) < -1 || _atof(nor[0]) > 1 || _atof(nor[1]) < -1 || \
		_atof(nor[1]) > 1 || _atof(nor[2]) < -1 || _atof(nor[2]) > 1)
		return (em_free(DIR_VECTOR, ori, nor, tab));
	cam->dir = (t_vec){_atof(nor[0]), _atof(nor[1]), _atof(nor[2])};
	if (!is_digitf(tab[3]) || (_atof(tab[3]) < 0 || _atof(tab[3]) > 180))
		return (em_free(FOV_ERR, ori, nor, tab));
	cam->fov = _atof(tab[3]);
	return (em_free(NULL, ori, nor, tab));
}

int	fill_light(t_light *light, char *line)
{
	char	**tab;
	char	**ori;
	char	**colors;
	int		color;

	tab = _split(line, ' ');
	if (tab[4])
		return (em_free(ARG_ERR, tab, NULL, NULL));
	if (_strlen(tab[0]) != 1 || tab[0][0] != 'L' || tab[0][1] != '\0')
		return (em_free("Light must start with 'L'", tab, NULL, NULL));
	ori = _split(tab[1], ',');
	if (!three_check(ori))
		return (em_free(ORIGIN_ERR, ori, tab, NULL));
	light->src = (t_vec){_atof(ori[0]), _atof(ori[1]), _atof(ori[2])};
	if (!is_digitf(tab[2]) || _atof(tab[2]) < 0 || _atof(tab[2]) > 1)
		return (em_free(INTENSITY, ori, tab, NULL));
	light->ratio = _atof(tab[2]);
	colors = _split(tab[3], ',');
	if (!three_check(colors))
		return (em_free(COLOR, ori, colors, tab));
	color = create_rgb(_atof(colors[0]), _atof(colors[1]), _atof(colors[2]));
	if (color == -1)
		return (em_free(COLOR, ori, colors, tab));
	light->col = (t_vec){_atof(colors[0]), _atof(colors[1]), _atof(colors[2])};
	return (em_free(NULL, ori, colors, tab));
}
