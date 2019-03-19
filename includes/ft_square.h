/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_square.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:56:06 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/01 17:59:35 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_square_H
# define FT_square_H

typedef struct	s_square
{
	t_triangle	*triangle1;
	t_triangle	*triangle2;
	int			color;
}				t_square;

t_square		*new_square(t_triangle *triangle1, t_triangle *triangle2, int color);
int				intersect_square(void *data, t_point pos_start,
								t_point vect_start, t_point *intersection_pos);
int				get_color_square(void *data, t_point intersection_pos);
t_point			get_normal_square(void *data, t_point intersection_pos);
void			objects_add_square(t_data *data, t_square *square);

#endif
