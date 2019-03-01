/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 18:15:14 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/01 18:35:43 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

t_cylinder
	*new_cylinder
	(t_point pos,
	t_point vect,
	double h,
	double rad,
	int color)
{
	t_cylinder	*cylinder;

	if ((cylinder = (t_cylinder *)malloc(sizeof(t_cylinder))) == NULL)
		return (NULL);
	cylinder->pos = pos;
	cylinder->vect = vect;
	cylinder->h = h;
	cylinder->rad = rad;
	cylinder->color = color;
	return (cylinder);
}

int
	intersect_cylinder
	(void *data,
	t_point pos_start,
	t_point vect_start,
	t_point *intersection_pos)
{
	t_cylinder	*cyl;

	cyl = (t_cylinder *)data;
	pos_start = vector_new(pos_start.x - cyl->pos.x, pos_start.y - cyl->pos.y, pos_start.z - cyl->pos.z);
	return (0);
}

int
	get_color_cylinder
	(void *data,
	t_point intersection_pos)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)data;
	return (cylinder->color);
}

t_point
	get_normal_cylinder
	(void *data,
	t_point intersection_pos)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)data;
	return (cylinder->vect);
}

void
	objects_add_cylinder
	(t_data *data,
	t_cylinder *cylinder)
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
	objects[index]->data = cylinder;
	objects[index]->intersect = intersect_cylinder;
	objects[index]->get_color = get_color_cylinder;
	objects[index]->get_normal_vector = get_normal_cylinder;
	if (data->mydata->objects_count > 1)
		free(data->mydata->objects);
	data->mydata->objects = objects;
}
