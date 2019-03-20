/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 16:44:39 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/20 02:09:07 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

void
	objects_add_sphere
	(t_data *data,
	t_sphere *sphere)
{
	t_obj3d	**objects;
	int		index;

	data->mydata->objects_count++;
	objects =
	(t_obj3d **)malloc(sizeof(t_obj3d *) * data->mydata->objects_count);
	index = -1;
	while (++index < (data->mydata->objects_count - 1))
		objects[index] = data->mydata->objects[index];
	objects[index] = (t_obj3d *)malloc(sizeof(t_obj3d));
	objects[index]->data = sphere;
	objects[index]->intersect = intersect_sphere;
	objects[index]->get_color = get_color_sphere;
	objects[index]->get_normal_vector = get_normal_sphere;
	if (data->mydata->objects_count > 1)
		free(data->mydata->objects);
	data->mydata->objects = objects;
}

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
	sphere->rad = fabs(rad);
	sphere->color = color;
	return (sphere);
}

int
	get_color_sphere
	(void *data,
	t_point intersection_pos)
{
	int		color;

	color = ((t_sphere *)data)->color;
	return (color);
	ft_printf("", &intersection_pos);
}

t_point
	get_normal_sphere
	(void *data,
	t_point inter_pos)
{
	t_point		vect;
	t_point		pos;
	t_sphere	*s;

	s = (t_sphere *)data;
	pos = s->pos;
	vect = vector_mul(inter_pos, pos);
	vector_normalize(&vect);
	return (vect);
}
