/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 02:08:55 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/20 02:38:46 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

int
	intersect_sphere
	(void *data,
	t_point v_start,
	t_point v,
	t_point *intersection_pos)
{
	t_sphere	*s;
	float		a;
	float		b;
	float		c;
	float		d;

	s = (t_sphere *)data;
	a = v.x * v.x + v.y * v.y + v.z * v.z;
	b = 2 * (v.x * (v_start.x - s->pos.x) + v.y * (v_start.y - s->pos.y) +
		v.z * (v_start.z - s->pos.z));
	c = s->pos.x * s->pos.x + s->pos.y * s->pos.y + s->pos.z * s->pos.z +
		v_start.x * v_start.x + v_start.y * v_start.y + v_start.z * v_start.z -
		2 * (v_start.x * s->pos.x + v_start.y * s->pos.y + v_start.z * s->pos.z)
		- s->rad * s->rad;
	d = b * b - 4 * a * c;
	if (d < 0)
		return (0);

	float	sqrt_d;
	float	a_2;
	float	t_1;
	float	t_2;
	float	min_t;
	float	max_t;
	float	t;

	sqrt_d = sqrt(d);
	a_2 = a * 2;
	t_1 = (-b + sqrt_d) / a_2;
	t_2 = (-b - sqrt_d) / a_2;
	min_t = (t_1 < t_2) ? t_1 : t_2;
	max_t = (t_1 < t_2) ? t_2 : t_1;
	t = (min_t > EPSILON) ? min_t : max_t;
	if (t < EPSILON)
		return (0);
	*intersection_pos =
	vector_new(v_start.x + t * v.x, v_start.y + t * v.y, v_start.z + t * v.z);
	return (1);
}
