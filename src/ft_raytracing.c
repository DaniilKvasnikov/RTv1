/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raytracing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 16:09:36 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/02/23 03:35:07 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

void
	ft_raytracing
	(t_data *data,
	int pos[2],
	t_point vect,
	void *obj)
{
	t_point		inter_pos;
	t_point		v;
	float		len;
	float		delta;

	if (intersect_sphere(
			obj,
			data->mydata->pos,
			vect,
			&inter_pos) == 1)
	{
		v = vector_mul(data->mydata->pos, inter_pos);
		len = module_vector(&v);
		if (len < data->mydata->depth[pos[X_P] + pos[Y_P] * WIN_W])
		{
			data->mydata->depth[pos[X_P] + pos[Y_P] * WIN_W] = len;
			v = get_normal_sphere(obj, inter_pos);
			delta = fabs(vector_sum(&v, &vect));
			ft_draw_px(data, pos[X_P], pos[Y_P],
			get_color_sphere(obj, inter_pos));
//			0x000088 * delta);
		}
	}
}
