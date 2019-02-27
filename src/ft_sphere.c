/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 16:44:39 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/02/27 17:43:19 by rrhaenys         ###   ########.fr       */
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
	sphere->rad = rad;
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
	vect = vector_mul(pos, inter_pos);
	vector_normalize(&vect);
	return (vect);
}

int
	intersect_sphere
	(void *data,
	t_point v_start,
	t_point v,
	t_point *intersection_pos)
{
	t_sphere	*s;
	float		a;
	float		b;
	float		c;
	float		d;

	s = (t_sphere *)data;
	a = v.x * v.x + v.y * v.y + v.z * v.z;
	b = 2 * (v.x * (v_start.x - s->pos.x) + v.y * (v_start.y - s->pos.y) +
		v.z * (v_start.z - s->pos.z));
	c = s->pos.x * s->pos.x + s->pos.y * s->pos.y + s->pos.z * s->pos.z +
		v_start.x * v_start.x + v_start.y * v_start.y + v_start.z * v_start.z -
		2 * (v_start.x * s->pos.x + v_start.y * s->pos.y + v_start.z * s->pos.z)
		- s->rad * s->rad;
	d = b * b - 4 * a * c;
	if (d < 0)
		return (0);

	float	sqrt_d;
	float	a_2;
	float	t_1;
	float	t_2;
	float	min_t;
	float	max_t;
	float	t;

	sqrt_d = sqrt(d);
	a_2 = a * 2;
	t_1 = (-b + sqrt_d) / a_2;
	t_2 = (-b - sqrt_d) / a_2;
	min_t = (t_1 < t_2) ? t_1 : t_2;
	max_t = (t_1 < t_2) ? t_2 : t_1;
	t = (min_t > EPSILON) ? min_t : max_t;
	if (t < EPSILON)
		return (0);
	*intersection_pos =
	vector_new(v_start.x + t * v.x, v_start.y + t * v.y, v_start.z + t * v.z);
	return (1);
}
