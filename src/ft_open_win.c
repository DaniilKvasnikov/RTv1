/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_win.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 07:03:09 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/02/23 04:18:27 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void
	ft_start_game
	(t_data *data,
	int argc,
	char **argv)
{
	data->mydata = (t_mydata *)malloc(sizeof(t_mydata));
	data->mydata->pos = vector_new(0, 0, 0);
	data->mydata->angle = vector_new(0, 0, 0);
	data->mydata->dispx = vector_new(0.66 * (WIN_W / (float)WIN_H), 0, 0);
	data->mydata->dispy = vector_new(0, 0.66, 0);
	data->mydata->argc = argc;
	data->mydata->argv = argv;
	data->mydata->objects_count = 0;
	data->mydata->depth = (float *)malloc(sizeof(float) * (WIN_W * WIN_H));
	data->mydata->mat = (t_matrix *)malloc(sizeof(t_matrix));
	objects_add_sphere(data, new_sphere(vector_new(0, -0.01, 0.1), 0.02, 0x008800));
	objects_add_sphere(data, new_sphere(vector_new(0.05, -0.05, 0.2), 0.06, 0x880000));
}

void
	ft_open_win
	(char *str,
	int argc,
	char **argv)
{
	t_data	data;

	if (((data.mlx_ptr = mlx_init()) == 0) ||
		((data.mlx_win =
		mlx_new_window(data.mlx_ptr, WIN_W, WIN_H, str)) == NULL) ||
		((data.img = (t_img *)malloc(sizeof(t_img))) == NULL) ||
		((data.mydata = (t_mydata *)malloc(sizeof(t_mydata))) == NULL))
		return ;
	ft_start_game(&data, argc, argv);
	mlx_do_key_autorepeaton(data.mlx_ptr);
//	mlx_expose_hook(data.mlx_win, ft_draw, &data);
	mlx_loop_hook(data.mlx_ptr, ft_draw, &data);
	mlx_hook(data.mlx_win, 2, 1L << 2, key_press, &data);
	mlx_hook(data.mlx_win, 3, 1L << 3, key_release, &data);
	mlx_hook(data.mlx_win, 17, 1L << 17, ft_close, &data);
	data.img->img_ptr = mlx_new_image(data.mlx_ptr, WIN_W, WIN_H);
	data.img->data = (int *)mlx_get_data_addr(data.img->img_ptr,
		&data.img->bpp, &data.img->size_l, &data.img->endian);
	mlx_loop(data.mlx_ptr);
}
