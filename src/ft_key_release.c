/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_release.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 03:25:16 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/19 21:48:10 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

int
	key_release
	(int key,
	t_data *data)
{
	if (key == 53)
		ft_close(data);
	return (1);
}

void			player_turn(t_data *data, double dx, double dy)
{
	data->mydata->angle.x += dx;
	data->mydata->angle.y += dy;
}

int
	key_press
	(int key,
	t_data *data)
{
	if (key == 53)
		ft_close(data);
	if (key == 0)
		player_turn(data, 0.0, 0.02);
	if (key == 2)
		player_turn(data, 0.0, -0.02);
	if (key == 1)
		player_turn(data, 0.02, 0.0);
	if (key == 13)
		player_turn(data, -0.02, 0.0);
	if (ft_is_flag(data, "-k"))
		ft_printf("key_press=%d\n", key);
	return (1);
}
