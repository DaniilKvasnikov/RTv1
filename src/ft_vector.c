/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:47:33 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/02/23 07:01:36 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_point
	vector_new
	(double x,
	double y,
	double z)
{
	t_point	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_point
	vector_mul
	(t_point start,
	t_point end)
{
	t_point vector;

	vector.x = end.x - start.x;
	vector.y = end.y - start.y;
	vector.z = end.z - start.z;
	return (vector);
}

double
	vector_sum
	(t_point *a,
	t_point *b)
{
	return
	(a->x * b->x + a->y * b->y + a->z * b->z);
}

double
	module_vector
	(t_point *v)
{
	return (sqrt(vector_sum(v, v)));
}

void
	vector_normalize
	(t_point *vector)
{
	double module;

	module = module_vector(vector);
	vector->x = vector->x / module;
	vector->y = vector->y / module;
	vector->z = vector->z / module;
}
