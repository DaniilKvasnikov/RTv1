/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 01:50:51 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/20 13:48:12 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRUCTS_H
# define FT_STRUCTS_H

typedef struct			s_matrix
{
	double				elem[4][4];
}						t_matrix;

typedef struct			s_point
{
	double				x;
	double				y;
	double				z;
}						t_point;

typedef struct			s_img
{
	void				*img_ptr;
	int					*data;
	int					size_l;
	int					bpp;
	int					endian;
}						t_img;

typedef struct			s_obj3d
{
	void				*data;
	int					(*intersect)(void *data, t_point pos_start,
								t_point vect_start, t_point *intersection_pos);
	int					(*get_color)(void *data, t_point intersection_pos);
	t_point				(*get_normal_vector)(void *data,
								t_point intersection_pos);
}						t_obj3d;

typedef struct			s_lights
{
	int					light_count;
	t_point				*light;
	double				*l_pows;
}						t_lights;

typedef struct			s_parsed
{
	int					type;
	t_point				pos;
	t_point				vect;
	t_point				p1;
	t_point				p2;
	t_point				p3;
	float				rad;
	double				color;
	double				h;
	double				l_pow;
	struct s_parsed		*next;
}						t_parsed;

typedef struct			s_mydata
{
	t_point				pos;
	t_point				angle;
	t_point				dispx;
	t_point				dispy;
	double				*depth;
	char				**argv;
	int					argc;
	int					fd;
	char				*input;
	t_matrix			*mat;
	t_parsed			*parsed_obj;
	t_obj3d				**objects;
	t_lights			*lights;
	int					objects_count;
}						t_mydata;

typedef struct			s_data
{
	void				*mlx_ptr;
	void				*mlx_win;
	t_img				*img;
	t_mydata			*mydata;
}						t_data;

#endif
