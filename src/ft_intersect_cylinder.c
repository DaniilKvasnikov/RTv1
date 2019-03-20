/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 05:58:32 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/20 06:03:44 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

int
	clipobj
	(t_point *raybase,
	t_point *raycos,
	t_plane2 *bot,
	t_plane2 *top,
	double *objin,
	double *objout,
	int *surfin,
	int *surfout)
{
	double	dc;
	double	dw;
	double	t;
	double	in;
	double	out;

	*surfin = 0;
	*surfout = 0;
	in = *objin;
	out = *objout;
	dc = bot->a * raycos->x + bot->b * raycos->y + bot->c * raycos->z;
	dw =
	bot->a * raybase->x + bot->b * raybase->y + bot->c * raybase->z + bot->d;
	if (dc == 0.0)
	{
		if (dw >= 0.0)
			return (0);
	}
	else
	{
		t = -dw / dc;
		if (dc >= 0.0)
		{
			if (t > in && t < out)
			{
				out = t;
				*surfout = 1;
			}
			if (t < in)
				return (0);
		}
		else
		{
			if (t > in && t < out)
			{
				in = t;
				*surfin = 1;
			}
			if (t > out)
				return (0);
		}
	}
	dc = top->a * raycos->x + top->b * raycos->y + top->c * raycos->z;
	dw =
	top->a * raybase->x + top->b * raybase->y + top->c * raybase->z + top->d;
	if (dc == 0.0)
	{
		if (dw >= 0.0)
			return (0);
	}
	else
	{
		t = -dw / dc;
		if (dc >= 0.0)
		{
			if (t > in && t < out)
			{
				out = t;
				*surfout = 2;
			}
			if (t < in)
				return (0);
		}
		else
		{
			if (t > in && t < out)
			{
				in = t;
				*surfin = 2;
			}
			if (t > out)
				return (0);
		}
	}
	*objin = in;
	*objout = out;
	return (in < out);
}

int
	intersect_cylinder2
	(t_point raybase,
	t_point raycos,
	t_point base,
	t_point axis,
	double radius,
	double *in,
	double *out)
{
	int				hit;
	t_point			rc;
	double			d;
	double			t;
	double			s;
	t_point			n;
	t_point			v_d;
	t_point			o;
	double			ln;
	const double	pinf = HUGE;

	rc = vector_new(raybase.x - base.x, raybase.y - base.y, raybase.z - base.z);
	n = cross_product(raycos, axis);

	if ((ln = module_vector(&n)) == 0)
	{
		d = vector_sum(&rc, &axis);
		v_d =
		vector_new(rc.x - d * axis.x, rc.y - d * axis.y, rc.z - d * axis.z);
		d = module_vector(&v_d);
		*in = -pinf;
		*out = pinf;
		return (d <= radius);
	}
	vector_normalize(&n);
	d = fabs(vector_sum(&rc, &n));
	hit = (d <= radius);
	if (hit)
	{
		o = cross_product(rc, axis);
		t = -vector_sum(&o, &n) / ln;
		o = cross_product(n, axis);
		vector_normalize(&o);
		s = fabs(sqrt(radius * radius - d * d) / vector_sum(&raycos, &o));
		*in = t - s;
		*out = t + s;
	}
	return (hit);
}

int
	intersect_cylinder
	(void *data,
	t_point pos_start,
	t_point vect_start,
	t_point *intersection_pos)
{
	t_cylinder	*cyl;
	double		in;
	double		out;
	int			surfin;
	int			surfout;
	int			res;
	t_plane2	bot;
	t_plane2	top;

	cyl = (t_cylinder *)data;
	bot.a = -cyl->vect.x;
	bot.b = -cyl->vect.y;
	bot.c = -cyl->vect.z;
	bot.d = cyl->vect.x * cyl->pos.x + cyl->vect.y * cyl->pos.y
	+ cyl->vect.z * cyl->pos.z;
	top.a = cyl->vect.x;
	top.b = cyl->vect.y;
	top.c = cyl->vect.z;
	top.d = -cyl->vect.x * cyl->pos2.x - cyl->vect.y * cyl->pos2.y
	- cyl->vect.z * cyl->pos2.z;
	res = intersect_cylinder2(pos_start, vect_start, cyl->pos, cyl->vect,
	cyl->rad, &in, &out);
	if (in < 0)
		return (0);
	if (cyl->h != 0)
		res = res && clipobj(&pos_start, &vect_start,
		&bot, &top, &in, &out, &surfin, &surfout);
	*intersection_pos = vector_new(
		pos_start.x + (vect_start.x * in),
		pos_start.y + (vect_start.y * in),
		pos_start.z + (vect_start.z * in));
	return (res);
}
