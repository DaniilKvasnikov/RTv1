/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_lights.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 17:58:08 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/15 18:05:26 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void
	ft_add_lights
	(t_data *data,
	double x,
	double y,
	double z,
	double l_pow)
{
	int		index;
	t_point	*light;
	double	*l_pows;

	data->mydata->lights->light_count++;
	light =
	(t_point *)malloc(sizeof(t_point) * data->mydata->lights->light_count);
	l_pows =
	(double *)malloc(sizeof(double) * data->mydata->lights->light_count);
	index = -1;
	while (++index < (data->mydata->lights->light_count - 1))
	{
		light[index] = data->mydata->lights->light[index];
		l_pows[index] = data->mydata->lights->l_pows[index];
	}
	light[index].x = x;
	light[index].y = y;
	light[index].z = z;
	l_pows[index] = l_pow;
	if (data->mydata->lights->light_count > 1)
	{
		free(data->mydata->lights->light);
		free(data->mydata->lights->l_pows);
	}
	data->mydata->lights->light = light;
	data->mydata->lights->l_pows = l_pows;
}
