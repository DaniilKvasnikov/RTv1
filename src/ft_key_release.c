/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_release.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 03:25:16 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/02/22 17:02:55 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int
	key_release
	(int key,
	t_data *data)
{
	if (key == 53)
		ft_close(data);
	return (1);
}

int
	key_press
	(int key,
	t_data *data)
{
	if (key == 53)
		ft_close(data);
	if (ft_is_flag(data, "-k"))
		ft_printf("key_press=%d\n", key);
	return (1);
}
