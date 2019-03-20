/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 05:58:32 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/20 14:32:20 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

int
	clipobj2
	(double dc,
	double dw,
	double t,
	double in,
	double out,
	int *surfout,
	int *surfin,
	int new_)
{
	if (dc != 0.0)
	{
		t = -dw / dc;
		if (dc >= 0.0)
		{
			if (t > in && t < out)
			{
				out = t;
				*surfout = new_;
			}
			if (t < in)
				return (0);
		}
		else
		{
			if (t > in && t < out)
			{
				in = t;
				*surfin = new_;
			}
			if (t > out)
				return (0);
		}
	}
	return (1);
}

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
	double	in;
	double	out;

	*surfin = 0;
	*surfout = 0;
	in = *objin;
	out = *objout;
	dc = bot->a * raycos->x + bot->b * raycos->y + bot->c * raycos->z;
	dw =
	bot->a * raybase->x + bot->b * raybase->y + bot->c * raybase->z + bot->d;
	if (dc == 0.0 && dw >= 0.0)
		return (0);
	if (clipobj2(dc, dw, 0, in, out, surfout, surfin, 1) == 0)
		return (0);
	dc = top->a * raycos->x + top->b * raycos->y + top->c * raycos->z;
	dw =
	top->a * raybase->x + top->b * raybase->y + top->c * raybase->z + top->d;
	if ((dc == 0.0 && dw >= 0.0) ||
		clipobj2(dc, dw, 0, in, out, surfout, surfin, 2) == 0)
		return (0);
	*objin = in;
	*objout = out;
	return (in < out);
}

int
	intersect_cylinder3
	(t_intersect_cylinder3 ob)
{
	t_point			o;
	double			s;
	double			t;
	double			d;

	vector_normalize(&ob.n);
	d = fabs(vector_sum(&ob.rc, &ob.n));
	if (d <= ob.radius)
	{
		o = cross_product(ob.rc, ob.axis);
		t = -vector_sum(&o, &ob.n) / ob.ln;
		o = cross_product(ob.n, ob.axis);
		vector_normalize(&o);
		s = fabs(sqrt(ob.radius * ob.radius - d * d) /
		vector_sum(&ob.raycos, &o));
		*ob.in = t - s;
		*ob.out = t + s;
		return (1);
	}
	return (0);
}

int
	intersect_cylinder2
	(t_intersect_cylinder2 o)
{
	double			d;
	double			ln;
	t_point			v_d;
	t_point			n;
	t_point			rc;

	rc = vector_new(
		o.raybase.x - o.base.x, o.raybase.y - o.base.y, o.raybase.z - o.base.z);
	n = cross_product(o.raycos, o.axis);
	if ((ln = module_vector(&n)) == 0)
	{
		d = vector_sum(&rc, &o.axis);
		v_d = vector_new(
			rc.x - d * o.axis.x, rc.y - d * o.axis.y, rc.z - d * o.axis.z);
		*o.in = -HUGE;
		*o.out = HUGE;
		return (module_vector(&v_d) <= o.radius);
	}
	return (intersect_cylinder3((t_intersect_cylinder3)
		{o.raycos, o.axis, o.radius, o.in, o.out, n, rc, ln}));
}

static t_plane2
	set_pars
	(double a,
	double b,
	double c,
	double d)
{
	t_plane2	plane;

	plane.a = a;
	plane.b = b;
	plane.c = c;
	plane.d = d;
	return (plane);
}

int
	intersect_cylinder
	(void *data,
	t_point pos_start,
	t_point vect_start,
	t_point *intersection_pos)
{
	t_cylinder	*cyl;
	double		inter[2];
	int			surf[2];
	int			res;
	t_plane2	plane[2];

	cyl = (t_cylinder *)data;
	plane[0] = set_pars(-cyl->vect.x, -cyl->vect.y, -cyl->vect.z, cyl->vect.x *
	cyl->pos.x + cyl->vect.y * cyl->pos.y + cyl->vect.z * cyl->pos.z);
	plane[1] = set_pars(cyl->vect.x, cyl->vect.y, cyl->vect.z, -cyl->vect.x *
	cyl->pos2.x - cyl->vect.y * cyl->pos2.y - cyl->vect.z * cyl->pos2.z);
	res = intersect_cylinder2((t_intersect_cylinder2){pos_start, vect_start,
	cyl->pos, cyl->vect, cyl->rad, &inter[0], &inter[1]});
	if (inter[0] < 0)
		return (0);
	if (cyl->h != 0)
		res = res && clipobj(&pos_start, &vect_start,
		&plane[0], &plane[1], &inter[0], &inter[1], &surf[0], &surf[1]);
	*intersection_pos = vector_new(pos_start.x + (vect_start.x * inter[0]),
	pos_start.y + (vect_start.y * inter[0]),
	pos_start.z + (vect_start.z * inter[0]));
	return (res);
}
