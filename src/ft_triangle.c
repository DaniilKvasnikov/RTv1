/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triangle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 12:45:13 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/20 02:21:30 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

t_triangle
	*new_triangle(t_point p1, t_point p2, t_point p3, int color)
{
	t_triangle	*triangle;

	if ((triangle = (t_triangle *)malloc(sizeof(t_triangle))) == NULL)
		return (NULL);
	triangle->p1 = p1;
	triangle->p2 = p2;
	triangle->p3 = p3;
	triangle->color = color;
	triangle->norm = cross_product(vector_mul(p1, p3), vector_mul(p3, p2));
	vector_normalize(&triangle->norm);
	triangle->d = -(p1.x * triangle->norm.x +
	p1.y * triangle->norm.y + p1.z * triangle->norm.z);
	triangle->v_p1_p2 = vector_mul(p1, p2);
	triangle->v_p2_p3 = vector_mul(p2, p3);
	triangle->v_p3_p1 = vector_mul(p3, p1);
	return (triangle);
}

int
	get_color_triangle
	(void *data,
	t_point intersection_pos)
{
	t_triangle	*tr;

	tr = (t_triangle *)data;
	return (tr->color);
	ft_printf("", &intersection_pos);
}

t_point
	get_normal_triangle
	(void *data,
	t_point intersection_pos)
{
	t_triangle	*tr;
	t_point		norm;

	tr = (t_triangle *)data;
	norm = vector_new(-tr->norm.x, -tr->norm.y, -tr->norm.z);
	return (norm);
	ft_printf("", &intersection_pos);
}

void
	objects_add_triangle
	(t_data *data,
	t_triangle *triangle)
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
	objects[index]->data = triangle;
	objects[index]->intersect = intersect_triangle;
	objects[index]->get_color = get_color_triangle;
	objects[index]->get_normal_vector = get_normal_triangle;
	if (data->mydata->objects_count > 1)
		free(data->mydata->objects);
	data->mydata->objects = objects;
}
