/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_cone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 06:45:20 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/20 06:45:54 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

static t_plane2
	set_pars
	(void *data,
	t_point pos_start,
	t_point vect_start)
{
	t_cone		*cone;
	t_point		x;
	t_plane2	pars;

	cone = (t_cone *)data;
	x = vector_mul(cone->pos, pos_start);
	pars.a = vector_sum(&vect_start, &cone->vect);
	pars.a = vector_sum(&vect_start, &vect_start) -
	(1.0 + cone->rad * cone->rad) * pars.a * pars.a;
	pars.b = 2.0 * (vector_sum(&vect_start, &x) - (1.0 + cone->rad * cone->rad)
		* vector_sum(&vect_start, &cone->vect) * vector_sum(&x, &cone->vect));
	pars.c = vector_sum(&x, &cone->vect);
	pars.c = vector_sum(&x, &x) - (1 + cone->rad * cone->rad) * pars.c * pars.c;
	pars.d = pars.b * pars.b - 4 * pars.a * pars.c;
	if (fabs(pars.d) < EPSILON)
		pars.d = 0;
	return (pars);
}

int
	intersect_cone
	(void *data,
	t_point pos_start,
	t_point vect_start,
	t_point *intersection_pos)
{
	t_cone		*cone;
	t_plane2	pars;
	double		t1;
	double		t2;

	cone = (t_cone *)data;
	pars = set_pars(data, pos_start, vect_start);
	if (pars.d >= 0)
	{
		t1 = (-pars.b - sqrt(pars.d)) / (2 * pars.a);
		t2 = (-pars.b + sqrt(pars.d)) / (2 * pars.a);
		if ((t1 <= t2 && t1 >= 0) || (t1 >= 0 && t2 < 0))
		{
			*intersection_pos = vector_new(pos_start.x + vect_start.x * t1,
			pos_start.y + vect_start.y * t1, pos_start.z + vect_start.z * t1);
			return (1);
		}
		if ((t2 <= t1 && t2 >= 0) || (t2 >= 0 && t1 < 0))
		{
			*intersection_pos = vector_new(pos_start.x + vect_start.x * t2,
			pos_start.y + vect_start.y * t2, pos_start.z + vect_start.z * t2);
			return (1);
		}
	}
	return (0);
}
