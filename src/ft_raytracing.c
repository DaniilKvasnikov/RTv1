/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raytracing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 16:09:36 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/02/27 17:44:49 by rrhaenys         ###   ########.fr       */
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

void
	ft_raytracing
	(t_data *data,
	int pos[2],
	t_point vect,
	t_obj3d *obj)
{
	t_point		inter_pos;
	t_point		v;
	float		len;
	t_point		norm;
	int			color;
	t_point		light;
	double		delta;

	if (obj->intersect(obj->data, data->mydata->pos, vect, &inter_pos) == 1)
	{
		v = vector_mul(data->mydata->pos, inter_pos);
		len = module_vector(&v);
		if (len < data->mydata->depth[pos[X_P] + pos[Y_P] * WIN_W])
		{
			data->mydata->depth[pos[X_P] + pos[Y_P] * WIN_W] = len;
			norm = obj->get_normal_vector(obj->data, inter_pos);
			color = obj->get_color(obj->data, inter_pos);
			light = vector_new(inter_pos.x - 0,
			inter_pos.y - 10,
			inter_pos.z - 10);
			vector_normalize(&light);
			delta = vector_sum(&norm, &light);
			if (delta < 0)
				delta = 0;
			color = color_new(color, 0.2 + 0.8 * delta);
			ft_draw_px(data, pos[X_P], pos[Y_P], color);
		}
	}
}
