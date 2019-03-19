/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 19:44:56 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/20 02:13:57 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <mlx.h>
# include <math.h>
# include "ft_printf.h"
# include <fcntl.h>

# define WIN_H 500
# define WIN_W (WIN_H * 16 / 10)
# define WIN_S (WIN_W * WIN_H)

# define EPSILON 1e-5

# define B_SPACE 49
# define B_ESC 53
# define B_W 13
# define B_S 1
# define B_A 0
# define B_D 2
# define B_NUM_4 86
# define B_NUM_6 88

# define PRIN_RET(a,s) {if (a){ft_putendl(s); return (0);}}
# define BLOCK_1(a, b, c, d) {a -= b; c += d;}
# define BLOCK_2(a, b, c, d, e) {if ((a += e) >= b) BLOCK_1(a, b, c, d);}
# define SGN(x) ((x < 0) ? -1 : ((x > 0) ? 1 : 0))
# define MAX(x, y) ((x > y) ? x : y)

# define RGB_RED 0xff0000
# define RGB_GREEN 0x00ff00
# define RGB_BLUE 0x87cefa
# define RGB_WHITE 0xffffff
# define RGB_YELLOW 0xffff33
# define RGB_BLACK 0x000000

# define X_P 0
# define Y_P 1

# include "ft_structs.h"
# include "ft_sphere.h"
# include "ft_triangle.h"
# include "ft_square.h"
# include "ft_cylinder.h"
# include "ft_plane.h"
# include "ft_cone.h"

void			ft_open_win(char *str, int argc, char **argv);

int				ft_draw(t_data *data);
void			ft_draw_px(t_data *data, int x, int y, int color);
void			line_fast(t_data *env, double *p1, double *p2, int color);
void			ft_linefast_int(t_data *data, int *p1, int *p2, int color);
void			ft_clearwin(t_data *data);

int				key_press(int key, t_data *data);
int				key_release(int key, t_data *data);

int				ft_close(t_data *data);

int				ft_is_flag(t_data *data, char *str);

void			ft_raytracing
				(t_data *data, int pos[2], t_point vect, t_obj3d *obj);

double			vector_sum(t_point *a, t_point *b);
t_point			vector_mul(t_point start, t_point end);
t_point			vector_new(double x, double y, double z);
void			vector_normalize(t_point *vector);
double			module_vector(t_point *v);
t_point			cross_product(t_point a, t_point b);

t_point			ft_matrix_mul(t_point v, t_matrix *m);
void			ft_matrix_init
				(t_data *data, double a_x, double a_y, double a_z);

void			ft_parser(t_mydata *mydata);

void			ft_add_lights
				(t_data *data, t_point pos, double l_pow);

#endif
