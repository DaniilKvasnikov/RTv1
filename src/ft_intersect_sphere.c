/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 02:08:55 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/20 05:28:17 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

t_point
	fun
	(double d,
	t_point param,
	t_point v_start,
	t_point v)
{
	float	sqrt_d;
	float	a_2;
	float	t[3];
	float	min_t;
	float	max_t;

	sqrt_d = sqrt(d);
	a_2 = param.x * 2;
	t[0] = (-param.y + sqrt_d) / a_2;
	t[1] = (-param.y - sqrt_d) / a_2;
	min_t = (t[0] < t[1]) ? t[0] : t[1];
	max_t = (t[0] < t[1]) ? t[1] : t[0];
	t[2] = (min_t > EPSILON) ? min_t : max_t;
	if (t[2] < EPSILON)
		return (vector_new(0, 0, 0));
	return (vector_new(v_start.x + t[2] * v.x,
		v_start.y + t[2] * v.y, v_start.z + t[2] * v.z));
}

int
	intersect_sphere
	(void *data,
	t_point v_start,
	t_point v,
	t_point *intersection_pos)
{
	t_sphere	*s;
	t_point		param;
	double		d;

	s = (t_sphere *)data;
	param.x = v.x * v.x + v.y * v.y + v.z * v.z;
	param.y = 2 * (v.x * (v_start.x - s->pos.x) + v.y * (v_start.y - s->pos.y) +
		v.z * (v_start.z - s->pos.z));
	param.z = s->pos.x * s->pos.x + s->pos.y * s->pos.y + s->pos.z * s->pos.z +
		v_start.x * v_start.x + v_start.y * v_start.y + v_start.z * v_start.z -
		2 * (v_start.x * s->pos.x + v_start.y * s->pos.y + v_start.z * s->pos.z)
		- s->rad * s->rad;
	d = param.y * param.y - 4 * param.x * param.z;
	if (d < 0)
		return (0);
	*intersection_pos = fun(d, param, v_start, v);
	if (module_vector(intersection_pos) == 0)
		return (0);
	return (1);
}
