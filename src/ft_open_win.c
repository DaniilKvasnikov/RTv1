/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_win.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 07:03:09 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/20 00:39:35 by rrhaenys         ###   ########.fr       */
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
	data->mydata->mat = (t_matrix *)malloc(sizeof(t_matrix));
	data->mydata->pos = vector_new(0, 0, 0);
	data->mydata->angle = vector_new(0, 0, 0);
	data->mydata->dispx = vector_new(0.66 * (WIN_W / (double)WIN_H), 0, 0);
	data->mydata->dispy = vector_new(0, 0.66, 0);
	data->mydata->argc = argc;
	data->mydata->argv = argv;
	data->mydata->objects_count = 0;
	data->mydata->depth = (double *)malloc(sizeof(double) * (WIN_W * WIN_H));
	data->mydata->lights = (t_lights *)malloc(sizeof(t_lights));
	data->mydata->lights->light_count = 0;
	ft_add_lights(data, 10, 0, 0, 0.2);
	ft_add_lights(data, -10, 0, 0, 0.2);
	// ft_parser(data->mydata);
	objects_add_sphere(
		data,
		new_sphere(
			vector_new(0, 0, 12),
			2,
			0xff0000));
	objects_add_square(
		data,
		new_square(
			new_triangle(
				vector_new(-4, -4, 14),
				vector_new(-4, 4, 14),
				vector_new(4, 4, 14),
				0x00ff00),
			new_triangle(
				vector_new(-4, -4, 14),
				vector_new(4, -4, 14),
				vector_new(4, 4, 14),
				0x00ff00),
			0x008888));
	objects_add_triangle(
		data,
		new_triangle(
				vector_new(5, -5, 13),
				vector_new(-5, -5, 13),
				vector_new(5, 5, 13),
				0x00ff00));
	objects_add_cylinder(
		data,
		new_cylinder(
			vector_new(3, 0, 9),
			vector_new(0, -1, 0),
			1,
			1.0,
			0xff0000));
	objects_add_cone(
		data,
		new_cone(
			vector_new(0, 0, 10),
			vector_new(0, 1, 0),
			.25,
			0xff0000));
	objects_add_plane(
		data,
		new_plane(
			vector_new(0, 2, 10),
			vector_new(0, 1, 0),
			0xffff00));
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
