/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 03:08:31 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/02/23 03:56:04 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void
	line_fast
	(t_data *env,
	double *p1,
	double *p2,
	int color)
{
	int i;
	int x[2];
	int p[2];

	x[0] = abs((int)(p2[Y_P] - p1[Y_P])) >> 1;
	x[1] = abs((int)(p2[X_P] - p1[X_P])) >> 1;
	ft_draw_px(env, (p[0] = p1[X_P]),
				(p[1] = p1[Y_P]), color);
	if (((i = -1) == -1) && abs((int)(p2[X_P] - p1[X_P])) >=
		abs((int)(p2[Y_P] - p1[Y_P])))
		while (++i < abs((int)(p2[X_P] - p1[X_P])))
		{
			BLOCK_2(x[1], abs((int)(p2[X_P] - p1[X_P])), p[1],
			SGN(p2[Y_P] - p1[Y_P]), abs((int)(p2[Y_P] - p1[Y_P])));
			ft_draw_px(env, (p[0] += SGN(p2[X_P] - p1[X_P])), p[1], color);
		}
	else
		while (++i < abs((int)(p2[Y_P] - p1[Y_P])))
		{
			BLOCK_2(x[0], abs((int)(p2[Y_P] - p1[Y_P])), p[0],
			SGN(p2[X_P] - p1[X_P]), abs((int)(p2[X_P] - p1[X_P])));
			ft_draw_px(env, p[0], (p[1] += SGN(p2[Y_P] - p1[Y_P])), color);
		}
}

void
	ft_draw_px
	(t_data *data,
	int x,
	int y,
	int color)
{
	data->img->data[y * WIN_W + x] = color;
}

int
	ft_draw
	(t_data *data)
{
	int			pos[2];
	t_point		dispx;
	t_point		dispy;
	t_point		vect;
	t_sphere	*sphere1;

	ft_clearwin(data);
	pos[X_P] = -1;
	ft_matrix_init(data, data->mydata->angle.x, data->mydata->angle.y, data->mydata->angle.z);
	dispx = ft_matrix_mul(data->mydata->dispx, data->mydata->mat);
	dispy = ft_matrix_mul(data->mydata->dispy, data->mydata->mat);
	sphere1 = new_sphere(vector_new(0, 0, 0.1), 0.02, 0xff0000);
	while (++pos[X_P] < WIN_W)
	{
		pos[Y_P] = -1;
		while (++pos[Y_P] < WIN_H)
		{
			vect = ft_matrix_mul(vector_new(0, 0, 1), data->mydata->mat);
			vect.x += dispx.x * (pos[0] * 2 / (float)WIN_W - 1) + dispy.x * (pos[1] * 2 / (float)WIN_H - 1);
			vect.y += dispx.y * (pos[0] * 2 / (float)WIN_W - 1) + dispy.y * (pos[1] * 2 / (float)WIN_H - 1);
			vect.z += dispx.z * (pos[0] * 2 / (float)WIN_W - 1) + dispy.z * (pos[1] * 2 / (float)WIN_H - 1);
			ft_raytracing(data, pos, vect, sphere1);
		}
	}
	free(sphere1);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
		data->img->img_ptr, 0, 0);
	return (1);
}
