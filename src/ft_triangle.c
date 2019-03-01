/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triangle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 12:45:13 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/01 14:02:55 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

int
	check_dir
	(t_point v1,
	t_point v2,
	t_point norm)
{
	t_point	norm_v1_v2;

	norm_v1_v2 = cross_product(v2, v1);
	if (vector_sum(&norm_v1_v2, &norm) < 0)
		return (0);
	else
		return (1);
}

t_triangle		*new_triange(t_point p1, t_point p2, t_point p3, int color)
{
	t_triangle	*triangle;

	if ((triangle = (t_triangle *)malloc(sizeof(t_triangle))) == NULL)
		return (NULL);
	triangle->p1 = p1;
	triangle->p2 = p2;
	triangle->p3 = p3;
	triangle->color = color;
	triangle->norm = cross_product(vector_mul(p1, p3), vector_mul(p3, p2));
	triangle->d = -(p1.x * triangle->norm.x +
	p1.y * triangle->norm.y + p1.z * triangle->norm.z);
	triangle->v_p1_p2 = vector_mul(p1, p2);
	triangle->v_p2_p3 = vector_mul(p2, p3);
	triangle->v_p3_p1 = vector_mul(p3, p1);
	return (triangle);
}

int
	intersect_triange
	(void *data,
	t_point pos_start,
	t_point vect_start,
	t_point *intersection_pos)
{
	t_triangle	*tr;
	float		scalar_product;
	float		k;

	tr = (t_triangle *)data;
	scalar_product = vector_sum(&(tr->norm), &vect_start);
//	printf("intersect_triange %d %lf %lf %lf\n", 1, tr->norm.x, tr->norm.y, tr->norm.z);
	if (fabs(scalar_product) < EPSILON)
		return (0);
	k = -(tr->norm.x * pos_start.x + tr->norm.y * pos_start.y
		+ tr->norm.z * pos_start.z + tr->d) / scalar_product;
//	printf("intersect_triange %d %f\n", 2, k);
	if (fabs(k) < EPSILON)
		return (0);

	float		x;
	float		y;
	float		z;
	t_point		ipt;

	x = pos_start.x + vect_start.x * k;
	y = pos_start.y + vect_start.y * k;
	z = pos_start.z + vect_start.z * k;
	ipt = vector_new(x, y, z);
//	printf("intersect_triange %d\n", 3);
	if (check_dir(tr->v_p1_p2, vector_mul(tr->p1, ipt), tr->norm)
		&& check_dir(tr->v_p2_p3, vector_mul(tr->p2, ipt), tr->norm)
		&& check_dir(tr->v_p3_p1, vector_mul(tr->p3, ipt), tr->norm))
	{
		*intersection_pos = ipt;
		return (1);
	}
//	printf("intersect_triange %d\n", 4);
	return (0);
}

int
	get_color_triange
	(void *data,
	t_point intersection_pos)
{
	t_triangle	*tr;

	tr = (t_triangle *)data;
	return (tr->color);
}

t_point
	get_normal_triange
	(void *data,
	t_point intersection_pos)
{
	t_triangle	*tr;

	tr = (t_triangle *)data;
	return (tr->norm);
}

void
	objects_add_triange
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
	objects[index]->intersect = intersect_triange;
	objects[index]->get_color = get_color_triange;
	objects[index]->get_normal_vector = get_normal_triange;
	if (data->mydata->objects_count > 1)
		free(data->mydata->objects);
	data->mydata->objects = objects;
}