/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raytracing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 16:09:36 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/04 20:42:13 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

int
	color_new
	(int color,
	double dcolor)
{
	int	r;
	int	g;
	int	b;

	r = dcolor * ((color >> 16) & 0xff);
	g = dcolor * ((color >> 8) & 0xff);
	b = dcolor * (color & 0xff);
	color = (r << 16) + (g << 8) + b;
	return (color);
}

int
	ft_shodow
	(t_data *data,
	t_point inter_pos,
	t_obj3d *this)
{
	t_point	light;
	t_point	shodow;
	float	len;
	float	new_len;
	int		index;
	t_obj3d	*obj;
	t_point	new_inter_pos;

	light = vector_mul(inter_pos, *(data->mydata->light));
	len = module_vector(&light);
	vector_normalize(&light);
	index = -1;
	while (++index < data->mydata->objects_count)
	{
		obj = data->mydata->objects[index];
		if (obj != this &&
		obj->intersect(obj->data, inter_pos, light, &new_inter_pos))
		{
			shodow = vector_mul(new_inter_pos, *(data->mydata->light));
			new_len = module_vector(&shodow);
			if (new_len < len)
				return (1);
		}
	}
	return (0);
}

void
	ft_raytracing
	(t_data *data,
	int pos[2],
	t_point vect,
	t_obj3d *obj)
{
	t_point		inter_pos;
	t_point		v;
	double		len;
	t_point		norm;
	int			color;
	t_point		light;
	double		delta;

	if (
//		(pos[Y_P] == (WIN_H / 2)) &&
//		(pos[X_P] == (WIN_W / 2 + 1)) &&
		obj->intersect(obj->data, data->mydata->pos, vect, &inter_pos) == 1)
	{
		v = vector_mul(data->mydata->pos, inter_pos);
		len = module_vector(&v);
		if (len < data->mydata->depth[pos[X_P] + pos[Y_P] * WIN_W])
		{
			data->mydata->depth[pos[X_P] + pos[Y_P] * WIN_W] = len;
			norm = obj->get_normal_vector(obj->data, inter_pos);
			color = obj->get_color(obj->data, inter_pos);
			light = vector_mul(*(data->mydata->light), inter_pos);
			vector_normalize(&light);
			delta = vector_sum(&norm, &light);
			delta = delta * (double)(delta >= 0);
			if (ft_shodow(data, inter_pos, obj) == 1)
				delta = 0.0;
			color = color_new(color, 0.3 + 0.7 * delta);
//			printf("%lf %lf %lf %lf\n", norm.x, norm.y, norm.z, delta);
			ft_draw_px(data, pos[X_P], pos[Y_P], color);
		}
	}
}
