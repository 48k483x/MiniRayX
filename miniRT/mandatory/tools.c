/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahrou <achahrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:27:16 by achahrou          #+#    #+#             */
/*   Updated: 2024/07/10 12:27:58 by achahrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	free_4(char **t, char **o, char **n, char **c)
{
	if (t)
		free_tab(t);
	if (o)
		free_tab(o);
	if (n)
		free_tab(n);
	if (c)
		free_tab(c);
	return (1);
}

int	in_range(char **tab)
{
	if (_atof(tab[0]) > 1.0f || _atof(tab[0]) < -1.0f \
	|| _atof(tab[1]) > 1.0f || _atof(tab[1]) < -1.0f || \
		_atof(tab[2]) > 1.0f || _atof(tab[2]) < -1.0f)
		return (0);
	return (1);
}

int	check_two_nums(char *n1, char *n2)
{
	if (!is_digitf(n1) || _atof(n1) <= 0 || !is_digitf(n2) || _atof(n2) <= 0)
		return (0);
	return (1);
}
