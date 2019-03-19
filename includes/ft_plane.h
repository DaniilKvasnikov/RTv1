/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:56:06 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/19 19:51:26 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PLANE_H
# define FT_PLANE_H

typedef struct	s_plane
{
	t_point		pos;
	t_point		norm;
	int			color;
}				t_plane;

t_plane			*new_plane(t_point pos, t_point norm, int color);
int				intersect_plane(void *data, t_point pos_start,
								t_point vect_start, t_point *intersection_pos);
int				get_color_plane(void *data, t_point intersection_pos);
t_point			get_normal_plane(void *data, t_point intersection_pos);
void			objects_add_plane(t_data *data, t_plane *plane);

#endif
