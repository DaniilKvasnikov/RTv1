/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 02:03:25 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/20 02:03:38 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
