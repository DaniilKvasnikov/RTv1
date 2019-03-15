/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cone.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:30:54 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/15 16:48:44 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONE_H
# define FT_CONE_H

typedef struct	s_cone
{
	t_point		pos;
	t_point		vect;
	double		rad;
	int			color;
}				t_cone;

t_cone			*new_cone(t_point pos, t_point vect, double rad, int color);
int				intersect_cone(void *data, t_point pos_start, t_point vect_start, t_point *intersection_pos);
int				get_color_cone(void *data, t_point intersection_pos);
t_point			get_normal_cone(void *data, t_point intersection_pos);
void			objects_add_cone(t_data *data, t_cone *cone);

#endif
