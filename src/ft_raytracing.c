/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raytracing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 16:09:36 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/20 05:13:29 by rrhaenys         ###   ########.fr       */
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
	t_obj3d *this,
	int l_num)
{
	t_point	point[2];
	float	len;
	int		index;
	t_obj3d	*obj;
	t_point	n_inter_pos;

	point[0] = vector_mul(inter_pos, data->mydata->lights->light[l_num]);
	len = module_vector(&point[0]);
	vector_normalize(&point[0]);
	index = -1;
	while (++index < data->mydata->objects_count)
	{
		obj = data->mydata->objects[index];
		if (obj != this &&
		obj->intersect(obj->data, inter_pos, point[0], &n_inter_pos))
		{
			point[1] =
			vector_mul(n_inter_pos, data->mydata->lights->light[l_num]);
			if (module_vector(&point[1]) < len &&
				vector_sum(&point[1], &point[0]) >= 0)
				return (1);
		}
	}
	return (0);
}

double
	ft_get_delta_light
	(t_data *data,
	t_point inter_pos,
	t_obj3d *obj)
{
	double	delta;
	double	n_delta;
	t_point	light;
	t_point	norm;
	int		index;

	index = -1;
	delta = 0.0;
	while (++index < data->mydata->lights->light_count)
	{
		norm = obj->get_normal_vector(obj->data, inter_pos);
		light = vector_mul(data->mydata->lights->light[index], inter_pos);
		vector_normalize(&norm);
		vector_normalize(&light);
		n_delta = vector_sum(&norm, &light);
		n_delta = n_delta * (double)(n_delta >= 0);
		if (ft_shodow(data, inter_pos, obj, index) == 0)
		{
			delta += (data->mydata->lights->l_pows[index] * n_delta);
			if (n_delta > 0.98)
				return (-(n_delta - 0.98) * 50.0);
		}
	}
	return (delta);
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
	int			color;
	double		delta;

	if (obj->intersect(obj->data, data->mydata->pos, vect, &inter_pos) == 1)
	{
		v = vector_mul(data->mydata->pos, inter_pos);
		len = module_vector(&v);
		if (len < data->mydata->depth[pos[X_P] + pos[Y_P] * WIN_W])
		{
			data->mydata->depth[pos[X_P] + pos[Y_P] * WIN_W] = len;
			color = obj->get_color(obj->data, inter_pos);
			delta = ft_get_delta_light(data, inter_pos, obj);
			if (delta >= 0.9)
				delta = 0.9;
			if (delta >= 0)
				color = color_new(color, 0.1 + delta);
			else
				color = color + color_new(0xffffff - color, -delta);
			ft_draw_px(data, pos[X_P], pos[Y_P], color);
		}
	}
}
