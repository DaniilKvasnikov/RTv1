/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:47:33 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/02/22 17:57:36 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_point
	new_vector
	(t_point start,
	t_point end)
{
	t_point vector;

	vector.pos[0] = end.pos[0] - start.pos[0];
	vector.pos[1] = end.pos[1] - start.pos[1];
	vector.pos[2] = end.pos[2] - start.pos[2];
	return (vector);
}

float
	module_vector
	(t_point *vector)
{
	float	module;
}

void
	vector_normalize
	(t_point *vector)
{
	float module;

	module = module_vector(vector);
	vector->pos[0] = vector->pos[0] / module;
	vector->pos[1] = vector->pos[1] / module;
	vector->pos[2] = vector->pos[2] / module;
}
