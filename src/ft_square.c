/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_square.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:24:07 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/19 23:16:53 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

t_square
	*new_square
	(t_triangle *triangle1,
	t_triangle *triangle2,
	int color)
{
	t_square *square;

	if ((square = (t_square *)malloc(sizeof(t_square))) == NULL)
		return (NULL);
	square->triangle1 = triangle1;
	square->triangle2 = triangle2;
	square->color = color;
	return (square);
}

int
	intersect_square
	(void *data,
	t_point pos_start,
	t_point vect_start,
	t_point *intersection_pos)
{
	t_triangle *t1;
	t_triangle *t2;

	t1 = ((t_square *)data)->triangle1;
	t2 = ((t_square *)data)->triangle2;
	return (intersect_triangle(t1, pos_start, vect_start, intersection_pos) ||
		intersect_triangle(t2, pos_start, vect_start, intersection_pos));
}

int
	get_color_square
	(void *data,
	t_point intersection_pos)
{
	t_square	*square;

	square = (t_square *)data;
	return (square->color);
	ft_printf("", &intersection_pos);
}

t_point
	get_normal_square
	(void *data,
	t_point intersection_pos)
{
	t_square	*square;

	square = (t_square *)data;
	return (square->triangle2->norm);
	ft_printf("", &intersection_pos);
}

void
	objects_add_square
	(t_data *data,
	t_square *square)
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
	objects[index]->data = square;
	objects[index]->intersect = intersect_square;
	objects[index]->get_color = get_color_square;
	objects[index]->get_normal_vector = get_normal_square;
	if (data->mydata->objects_count > 1)
		free(data->mydata->objects);
	data->mydata->objects = objects;
}
