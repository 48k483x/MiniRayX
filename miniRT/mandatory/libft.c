/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahrou <achahrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:26:50 by achahrou          #+#    #+#             */
/*   Updated: 2024/07/10 12:27:58 by achahrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	is_space(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}

char	*_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (i < len && big[i])
	{
		while ((i + j) < len && big[i + j] == little[j] && big[i + j])
			j++;
		if (little[j] == '\0')
			return ((char *)big + i);
		j = 0;
		i++;
	}
	return (NULL);
}

int	init_atof(t_help *h, char *str)
{
	if (!str)
		return (0);
	h->i = 0;
	h->factor = 1.0f;
	h->res = 0;
	h->sign = 1;
	return (1);
}

float	_atof(char *str)
{
	t_help	h;

	if (!init_atof(&h, str))
		return (-1);
	if (str[h.i] == '-')
	{
		h.sign = -1;
		h.i++;
	}
	while (str[h.i] >= '0' && str[h.i] <= '9')
	{
		h.res = h.res * 10 + str[h.i] - '0';
		h.i++;
	}
	if (str[h.i] == '.')
	{
		h.i++;
		while (str[h.i] >= '0' && str[h.i] <= '9')
		{
			h.factor /= 10.0f;
			h.res += (str[h.i] - '0') * h.factor;
			h.i++;
		}
	}
	return (h.res * h.sign);
}
