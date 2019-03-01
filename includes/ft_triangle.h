/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triangle.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 12:45:53 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/01 18:13:14 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TRIANGLE_H
# define FT_TRIANGLE_H

typedef struct	s_triangle
{
	t_point		p1;
	t_point		p2;
	t_point		p3;
	t_point		norm;
	int			color;
	float		d;
    t_point		v_p1_p2;
    t_point		v_p2_p3;
    t_point		v_p3_p1;
}				t_triangle;

t_triangle		*new_triangle(t_point p1, t_point p2, t_point p3, int color);
int				intersect_triangle(void *data, t_point pos_start,
								t_point vect_start, t_point *intersection_pos);
int				get_color_triangle(void *data, t_point intersection_pos);
t_point			get_normal_triangle(void *data, t_point intersection_pos);
void			objects_add_triangle(t_data *data, t_triangle *triangle);

#endif
