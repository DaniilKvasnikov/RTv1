/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:24:07 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/01 18:07:38 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

t_plane
	*new_plane
	(t_triangle *triangle1,
	t_triangle *triangle2,
	int color)
{
	t_plane *plane;

	if ((plane = (t_plane *)malloc(sizeof(t_plane))) == NULL)
		return (NULL);
	plane->triangle1 = triangle1;
	plane->triangle2 = triangle2;
	plane->color = color;
	return (plane);
}

int
	intersect_plane
	(void *data,
	t_point pos_start,
	t_point vect_start,
	t_point *intersection_pos)
{
	t_triangle *t1;
	t_triangle *t2;

	t1 = ((t_plane *)data)->triangle1;
	t2 = ((t_plane *)data)->triangle2;
	return (intersect_triange(t1, pos_start, vect_start, intersection_pos) ||
		intersect_triange(t2, pos_start, vect_start, intersection_pos));
}

int
	get_color_plane
	(void *data,
	t_point intersection_pos)
{
	t_plane	*plane;

	plane = (t_plane *)data;
	return (plane->color);
}

t_point
	get_normal_plane
	(void *data,
	t_point intersection_pos)
{
	t_plane	*plane;

	plane = (t_plane *)data;
	return (plane->triangle2->norm);
}

void
	objects_add_plane
	(t_data *data,
	t_plane *plane)
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
	objects[index]->data = plane;
	objects[index]->intersect = intersect_plane;
	objects[index]->get_color = get_color_plane;
	objects[index]->get_normal_vector = get_normal_plane;
	if (data->mydata->objects_count > 1)
		free(data->mydata->objects);
	data->mydata->objects = objects;
}
