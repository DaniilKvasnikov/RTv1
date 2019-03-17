/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 18:15:02 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/15 16:31:09 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CYLINDER_H
# define FT_CYLINDER_H

typedef struct	s_cylinder
{
	t_point		pos;
	t_point		vect;
	t_point		pos2;
	double		h;
	double		rad;
	int			color;
}				t_cylinder;

t_cylinder		*new_cylinder(t_point pos, t_point vect, double h, double rad, int color);
int				intersect_cylinder(void *data, t_point pos_start, t_point vect_start, t_point *intersection_pos);
int				get_color_cylinder(void *data, t_point intersection_pos);
t_point			get_normal_cylinder(void *data, t_point intersection_pos);
void			objects_add_cylinder(t_data *data, t_cylinder *cylinder);

#endif
