/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:38:31 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/02/23 02:05:09 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

void		ft_make_identety(t_matrix *m)
{
	m->elem[0][0] = 1;
	m->elem[0][1] = 0;
	m->elem[0][2] = 0;
	m->elem[0][3] = 0;
	m->elem[1][0] = 0;
	m->elem[1][1] = 1;
	m->elem[1][2] = 0;
	m->elem[1][3] = 0;
	m->elem[2][0] = 0;
	m->elem[2][1] = 0;
	m->elem[2][2] = 1;
	m->elem[2][3] = 0;
	m->elem[3][0] = 0;
	m->elem[3][1] = 0;
	m->elem[3][2] = 0;
	m->elem[3][3] = 1;
}

void		ft_clear_matrix(t_matrix *m)
{
	m->elem[0][0] = 0;
	m->elem[0][1] = 0;
	m->elem[0][2] = 0;
	m->elem[0][3] = 0;
	m->elem[1][0] = 0;
	m->elem[1][1] = 0;
	m->elem[1][2] = 0;
	m->elem[1][3] = 0;
	m->elem[2][0] = 0;
	m->elem[2][1] = 0;
	m->elem[2][2] = 0;
	m->elem[2][3] = 0;
	m->elem[3][0] = 0;
	m->elem[3][1] = 0;
	m->elem[3][2] = 0;
	m->elem[3][3] = 0;
}

t_point		ft_matrix_mul(t_point v, t_matrix *m)
{
	float x_n;
	float y_n;
	float z_n;

	x_n = v.x * m->elem[0][0] + v.y * m->elem[1][0]
	+ v.z * m->elem[2][0] + m->elem[3][0];
	y_n = v.x * m->elem[0][1] + v.y * m->elem[1][1]
	+ v.z * m->elem[2][1] + m->elem[3][1];
	z_n = v.x * m->elem[0][2] + v.y * m->elem[1][2]
	+ v.z * m->elem[2][2] + m->elem[3][2];
	v.x = x_n;
	v.y = y_n;
	v.z = z_n;
	return (v);
}

void		ft_matrix_init(t_data *data, double a_x, double a_y, double a_z)
{
	t_matrix	*mat;
	float		c[3];
	float		s[3];

	mat = data->mydata->mat;
	ft_make_identety(mat);
	c[0] = cos(a_x);
	c[1] = cos(a_y);
	c[2] = cos(a_z);
	s[0] = sin(a_x);
	s[1] = sin(a_y);
	s[2] = sin(a_z);
	mat->elem[0][0] = c[1] * c[2];
	mat->elem[0][1] = (s[0] * s[1] * c[2] - c[0] * s[2]);
	mat->elem[0][2] = (c[0] * s[1] * c[2] + s[0] * s[2]);
	mat->elem[1][0] = c[1] * s[2];
	mat->elem[1][1] = (s[0] * s[1] * s[2] + c[0] * c[2]);
	mat->elem[1][2] = (c[0] * s[1] * s[2] - s[0] * c[2]);
	mat->elem[2][0] = -s[1];
	mat->elem[2][1] = s[0] * c[1];
	mat->elem[2][2] = c[0] * c[1];
}
