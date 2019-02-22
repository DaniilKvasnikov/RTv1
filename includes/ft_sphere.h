/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 16:45:42 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/02/22 16:57:30 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SPHERE_H
# define FT_SPHERE_H

typedef struct	s_sphere
{
	t_point		pos;
	float		rad;
	int			color;
}				t_sphere;

t_sphere		*new_sphere(t_point pos, float rad, int color);
int				intersect_sphere(void *data, t_point pos_start,
								t_point vect_start, t_point *intersection_pos);
int				get_color_sphere(void *data, t_point intersection_pos);
t_point			get_normal_sphere(void *data, t_point intersection_pos);

#endif
