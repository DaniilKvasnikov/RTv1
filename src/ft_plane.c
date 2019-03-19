/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:24:07 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/19 23:16:58 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_plane
	*new_plane
	(t_point pos,
	t_point norm,
	int color)
{
	t_plane *plane;

	if ((plane = (t_plane *)malloc(sizeof(t_plane))) == NULL)
		return (NULL);
	plane->pos = pos;
	plane->norm = norm;
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
	t_plane	*plane;
	t_point	diff;
	double	delta;

	plane = ((t_plane *)data);
	if (vector_sum(&vect_start, &plane->norm) == 0)
		return (0);
	diff = vector_mul(plane->pos, pos_start);
	delta =
	-vector_sum(&diff, &plane->norm) / vector_sum(&vect_start, &plane->norm);
	if (delta < 0)
		return (0);
	*intersection_pos = vector_new(
		diff.x + plane->pos.x + delta * vect_start.x,
		diff.y + plane->pos.y + delta * vect_start.y,
		diff.z + plane->pos.z + delta * vect_start.z);
	return (1);
}

int
	get_color_plane
	(void *data,
	t_point intersection_pos)
{
	t_plane	*plane;

	plane = (t_plane *)data;
	return (plane->color);
	ft_printf("", &intersection_pos);
}

t_point
	get_normal_plane
	(void *data,
	t_point intersection_pos)
{
	t_plane	*plane;

	plane = (t_plane *)data;
	return (plane->norm);
	ft_printf("", &intersection_pos);
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
