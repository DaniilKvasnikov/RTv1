/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 18:15:14 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/20 06:41:01 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

t_cylinder
	*new_cylinder
	(t_point pos,
	t_point vect,
	t_point h_rad,
	int color)
{
	t_cylinder	*cylinder;

	if ((cylinder = (t_cylinder *)malloc(sizeof(t_cylinder))) == NULL)
		return (NULL);
	cylinder->pos = pos;
	cylinder->vect = vect;
	cylinder->h = fabs(h_rad.x);
	vector_normalize(&cylinder->vect);
	cylinder->pos2 = vector_new(
				cylinder->pos.x + (cylinder->vect.x * cylinder->h),
				cylinder->pos.y + (cylinder->vect.y * cylinder->h),
				cylinder->pos.z + (cylinder->vect.z * cylinder->h));
	cylinder->rad = fabs(h_rad.y);
	cylinder->color = color;
	return (cylinder);
}

int
	get_color_cylinder
	(void *data,
	t_point intersection_pos)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)data;
	return (cylinder->color);
	ft_printf("", &intersection_pos);
}

t_point
	get_normal_cylinder
	(void *data,
	t_point intersection_pos)
{
	t_cylinder	*cylinder;
	double		angle;
	t_point		vect;
	double		len;

	cylinder = (t_cylinder *)data;
	vect = vector_mul(cylinder->pos, intersection_pos);
	len = module_vector(&vect);
	vector_normalize(&vect);
	angle = vector_sum(&cylinder->vect, &vect);
	len = len * angle;
	vect = vector_mul(
		intersection_pos,
		vector_new(cylinder->pos.x + cylinder->vect.x * len,
					cylinder->pos.y + cylinder->vect.y * len,
					cylinder->pos.z + cylinder->vect.z * len));
	len = module_vector(&vect);
	vector_normalize(&vect);
	if (len < (cylinder->rad - 0.001))
		vect = vector_new(cylinder->vect.x * (1 - 2 * (angle >= 0.01)),
			cylinder->vect.y * (1 - 2 * (angle >= 0.01)),
			cylinder->vect.z * (1 - 2 * (angle >= 0.01)));
	return (vect);
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
