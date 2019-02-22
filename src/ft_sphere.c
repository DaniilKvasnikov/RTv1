/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 16:44:39 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/02/22 17:52:52 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_sphere
	*new_sphere
	(t_point pos,
	float rad,
	int color)
{
	t_sphere	*sphere;

	if ((sphere = (t_sphere *)malloc(sizeof(t_sphere))) == NULL)
		return (NULL);
	sphere->pos = pos;
	sphere->rad = rad;
	sphere->color = color;
	return (sphere);
}

int
	get_color_sphere
	(void *data,
	t_point intersection_pos)
{
	int	color;

	color = ((t_sphere *)data)->color;
	return (color);
}

t_point
	get_normal_sphere
	(void *data,
	t_point intersection_pos)
{
	t_point vect;

	vect = new_vector(((t_sphere *)data)->pos, intersection_pos);
	vector_normalize(&vect);
	return (vect);
}

int
	intersect_sphere
	(void *data,
	t_point pos_start,
	t_point vect_start,
	t_point *intersection_pos)
{
	return (0);
}
