/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cone.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:30:45 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/20 06:45:47 by rrhaenys         ###   ########.fr       */
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
	cone->rad = fabs(rad);
	cone->color = color;
	return (cone);
}

int
	get_color_cone
	(void *data,
	t_point intersection_pos)
{
	t_cone	*cone;

	cone = (t_cone *)data;
	return (cone->color);
	ft_printf("", &intersection_pos);
}

t_point
	get_normal_cone
	(void *data,
	t_point intersection_pos)
{
	t_cone		*cone;
	double		angle;
	t_point		vect;
	double		len;

	cone = (t_cone *)data;
	vect = vector_mul(cone->pos, intersection_pos);
	len = module_vector(&vect);
	vector_normalize(&vect);
	angle = vector_sum(&cone->vect, &vect);
	len = len * (1 - 2 * (angle < 0));
	vect = vector_mul(
		intersection_pos,
		vector_new(
		cone->pos.x + cone->vect.x * len,
		cone->pos.y + cone->vect.y * len,
		cone->pos.z + cone->vect.z * len));
	len = module_vector(&vect);
	vector_normalize(&vect);
	return (vect);
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
