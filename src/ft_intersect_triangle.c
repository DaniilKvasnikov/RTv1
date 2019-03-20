/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_triangle.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 02:06:51 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/20 02:21:33 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

int
	check_dir
	(t_point v1,
	t_point v2,
	t_point norm)
{
	t_point	norm_v1_v2;

	norm_v1_v2 = cross_product(v2, v1);
	if (vector_sum(&norm_v1_v2, &norm) < 0)
		return (0);
	else
		return (1);
}

int
	intersect_triangle
	(void *data,
	t_point pos_start,
	t_point vect_start,
	t_point *intersection_pos)
{
	t_triangle	*tr;
	float		scalar_product;
	float		k;

	tr = (t_triangle *)data;
	scalar_product = vector_sum(&(tr->norm), &vect_start);
	if (fabs(scalar_product) < EPSILON)
		return (0);
	k = -(tr->norm.x * pos_start.x + tr->norm.y * pos_start.y
		+ tr->norm.z * pos_start.z + tr->d) / scalar_product;
	if (k < EPSILON)
		return (0);

	float		x;
	float		y;
	float		z;
	t_point		ipt;

	x = pos_start.x + vect_start.x * k;
	y = pos_start.y + vect_start.y * k;
	z = pos_start.z + vect_start.z * k;
	ipt = vector_new(x, y, z);
	if (check_dir(tr->v_p1_p2, vector_mul(tr->p1, ipt), tr->norm)
		&& check_dir(tr->v_p2_p3, vector_mul(tr->p2, ipt), tr->norm)
		&& check_dir(tr->v_p3_p1, vector_mul(tr->p3, ipt), tr->norm))
	{
		*intersection_pos = ipt;
		return (1);
	}
	return (0);
}
