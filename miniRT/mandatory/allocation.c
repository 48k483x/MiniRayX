/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahrou <achahrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:26:15 by achahrou          #+#    #+#             */
/*   Updated: 2024/07/12 06:42:40 by achahrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_objs	*alloc_objs(t_scene *sc)
{
	t_objs	*new_obj;

	new_obj = malloc(sizeof(t_objs));
	if (!new_obj)
		return (NULL);
	null_vec(&(new_obj->col));
	null_vec(&(new_obj->cen));
	null_vec(&(new_obj->dir));
	null_vec(&(new_obj->p));
	new_obj->next = sc->objs;
	sc->objs = new_obj;
	return (new_obj);
}
