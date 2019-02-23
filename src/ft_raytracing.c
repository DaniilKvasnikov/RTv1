/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raytracing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 16:09:36 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/02/23 08:17:11 by rrhaenys         ###   ########.fr       */
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
	t_point		start;
	int			color;

	if (obj->intersect(obj->data, data->mydata->pos, vect, &inter_pos) == 1)
	{
		v = vector_mul(data->mydata->pos, inter_pos);
		len = module_vector(&v);
		if (len < data->mydata->depth[pos[X_P] + pos[Y_P] * WIN_W])
		{
			data->mydata->depth[pos[X_P] + pos[Y_P] * WIN_W] = len;
			norm = obj->get_normal_vector(data, inter_pos);
			start = ((t_sphere *)obj->data)->pos;
			data->mydata->norm[pos[X_P] + pos[Y_P] * WIN_W] =
			(norm.x * start.x + norm.y * start.y + norm.z * start.z) /
			(sqrt(norm.x * norm.x + norm.y * norm.y + norm.z * norm.z) *
			sqrt(start.x * start.x + start.y * start.y + start.z * start.z));
			data->mydata->norm[pos[X_P] + pos[Y_P] * WIN_W] = 1 -
			(acos(data->mydata->norm[pos[X_P] + pos[Y_P] * WIN_W]) / (double)M_PI) * 4;
			color = color_new(obj->get_color(obj->data, inter_pos), (data->mydata->norm[pos[X_P] + pos[Y_P] * WIN_W]));
			ft_draw_px(data, pos[X_P], pos[Y_P],
			color);
		}
	}
}
