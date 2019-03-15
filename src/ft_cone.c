/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cone.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:30:45 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/15 17:31:47 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

t_cone
	*new_cone
	(t_point pos,
	t_point vect,
	double rad,
	int color)
{
	t_cone	*cone;

	if ((cone = (t_cone *)malloc(sizeof(t_cone))) == NULL)
		return (NULL);
	cone->pos = pos;
	cone->vect = vect;
	cone->rad = rad;
	cone->color = color;
	return (cone);
}

int
	intersect_cone
	(void *data,
	t_point pos_start,
	t_point vect_start,
	t_point *intersection_pos)
{
	t_cone	*cone;
	t_point	x;
	double	a;
	double	b;
	double	c;
	double	d;

	cone = (t_cone *)data;
	x = vector_mul(cone->pos, pos_start);
	a = vector_sum(&vect_start, &cone->vect);
	a = vector_sum(&vect_start, &vect_start) - (1.0 + cone->rad * cone->rad) * a * a;
	b = 2.0 * (vector_sum(&vect_start, &x) - (1.0 + cone->rad * cone->rad)
		* vector_sum(&vect_start, &cone->vect) * vector_sum(&x, &cone->vect));
	c = vector_sum(&x, &cone->vect);
	c = vector_sum(&x, &x) - (1 + cone->rad * cone->rad) * c * c;
	d = b * b - 4 * a * c;
	if (fabs(d) < EPSILON)
		d = 0;

	if (d >= 0)
	{
		double	t1;
		double	t2;

		t1 = (-b - sqrt(d)) / (2 * a);
		t2 = (-b + sqrt(d)) / (2 * a);
		if ((t1 <= t2 && t1 >= 0) || (t1 >= 0 && t2 < 0))
		{
			*intersection_pos =
			vector_new(pos_start.x + vect_start.x * t1,
						pos_start.y + vect_start.y * t1,
						pos_start.z + vect_start.z * t1);
			return (1);
		}
		if ((t2 <= t1 && t2 >= 0) || (t2 >= 0 && t1 < 0))
		{
			*intersection_pos =
			vector_new(pos_start.x + vect_start.x * t2,
						pos_start.y + vect_start.y * t2,
						pos_start.z + vect_start.z * t2);
			return (1);
		}
	}
	return (0);
}

int
	get_color_cone
	(void *data,
	t_point intersection_pos)
{
	t_cone	*cone;

	cone = (t_cone *)data;
	return (cone->color);
}

t_point
	get_normal_cone
	(void *data,
	t_point intersection_pos)
{
	t_cone	*cone;

	cone = (t_cone *)data;
	return (cone->vect);
}

void
	objects_add_cone
	(t_data *data,
	t_cone *cone)
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
	objects[index]->data = cone;
	objects[index]->intersect = intersect_cone;
	objects[index]->get_color = get_color_cone;
	objects[index]->get_normal_vector = get_normal_cone;
	if (data->mydata->objects_count > 1)
		free(data->mydata->objects);
	data->mydata->objects = objects;
}
