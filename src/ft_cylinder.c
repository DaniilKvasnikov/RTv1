/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 18:15:14 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/04 17:33:36 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

t_cylinder
	*new_cylinder
	(t_point pos,
	t_point vect,
	double h,
	double rad,
	int color)
{
	t_cylinder	*cylinder;

	if ((cylinder = (t_cylinder *)malloc(sizeof(t_cylinder))) == NULL)
		return (NULL);
	cylinder->pos = pos;
	cylinder->vect = vect;
	cylinder->h = h;
	vector_normalize(&cylinder->vect);
	cylinder->pos2 = vector_new(
				cylinder->pos.x + (cylinder->vect.x * cylinder->h),
				cylinder->pos.y + (cylinder->vect.y * cylinder->h),
				cylinder->pos.z + (cylinder->vect.z * cylinder->h));
	cylinder->rad = rad;
	cylinder->color = color;
	return (cylinder);
}
/* ---- clipobj - обрезать объект с помощью плоской пары. ------------------------ */
/* */
/* */
/* Описание: */
/* Clipobj обрезает предоставленный бесконечный объект двумя */
/* (верх и низ) ограничивающие плоскости. */
/* */
/* При входе: */
/* raybase = Базовая точка пересекающегося луча. */
/* raycos = Направляющие косинусы вышеупомянутого луча. (единица измерения) */
/* bot = Нормальное и перпендикулярное расстояние нижней плоскости */
/*. */
/* top = Нормальное и перпендикулярное расстояние верхней плоскости */
/*. */
/* objin = Входное расстояние пересечения с */
/* объектом. */
/* objout = Выходное расстояние пересечения с */
/* объектом. */
/* */
/* По возвращении: */
/* objin = Входное расстояние пересечения. */
/* objout = выходное расстояние пересечения. */
/* surfin = Идентификатор входящей поверхности. */
/* surfout = Идентификатор уходящей поверхности. */
/* */
/* Returns: True, если луч пересекает ограниченный объект. */
/* */
/* ------------------------------------------ -------------------------- */

#define		SIDE	0		/* Поверхность объекта		*/
#define		BOT	1		/* Нижняя поверхность торцевой крышки	*/
#define		TOP	2		/* Верхняя поверхность крышки	*/

/* Plane: ax + by + cz + d = 0	*/
typedef struct	s_plane2
{
	double		a;
	double		b;
	double		c;
	double		d;
}				t_plane2;

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
	double	dc, dw, t;
	double	in, out;		/* Object  intersection dists.	*/

	*surfin = *surfout = SIDE;
	in  = *objin;
	out = *objout;

/*	Intersect the ray with the bottom end-cap plane.		*/

	dc = bot->a*raycos->x  + bot->b*raycos->y  + bot->c*raycos->z;
	dw = bot->a*raybase->x + bot->b*raybase->y + bot->c*raybase->z + bot->d;

	if  ( dc == 0.0 ) {		/* If parallel to bottom plane	*/
	    if	( dw >= 0. ) return (0);
	} else {
	    t  = - dw / dc;
	    if	( dc >= 0.0 ) {			    /* If far plane	*/
		if  ( t > in && t < out ) { out = t; *surfout = BOT; }
		if  ( t < in  ) return (0);
	     } else {				    /* If near plane	*/
		if  ( t > in && t < out ) { in	= t; *surfin  = BOT; }
		if  ( t > out ) return (0);
	    }
	}

/*	Intersect the ray with the top end-cap plane.			*/

	dc = top->a*raycos->x  + top->b*raycos->y  + top->c*raycos->z;
	dw = top->a*raybase->x + top->b*raybase->y + top->c*raybase->z + top->d;

	if  ( dc == 0.0 ) {		/* If parallel to top plane	*/
	    if	( dw >= 0. ) return (0);
	} else {
	    t  = - dw / dc;
	    if	( dc >= 0.0 ) {			    /* If far plane	*/
		if  ( t > in && t < out ) { out = t; *surfout = TOP; }
		if  ( t < in  ) return (0);
	     } else {				    /* If near plane	*/
		if  ( t > in && t < out ) { in	= t; *surfin  = TOP; }
		if  ( t > out ) return (0);
	    }
	}

	*objin	= in;
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
	int			hit;
	t_point		RC;
	double		d;
	double		t;
	double		s;
	t_point		n;
	t_point		D;
	t_point		O;
	double		ln;
	const double	pinf = HUGE;

	RC = vector_new(raybase.x - base.x, raybase.y - base.y, raybase.z - base.z);
	n = cross_product(raycos,axis);

	if ((ln = module_vector(&n)) == 0)
	{
		d = vector_sum(&RC,&axis);
		D = vector_new(RC.x - d*axis.x, RC.y - d*axis.y, RC.z - d*axis.z);
		d = module_vector(&D);
		*in = -pinf;
		*out = pinf;
		return (d <= radius);
	}
	vector_normalize(&n);
	d = fabs(vector_sum(&RC,&n));
	hit = (d <= radius);
	if (hit)
	{
		O = cross_product(RC,axis);
		t = -vector_sum(&O,&n) / ln;
		O = cross_product(n,axis);
		vector_normalize(&O);
		s = fabs(sqrt(radius * radius - d * d) / vector_sum(&raycos, &O));
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
	double		surfin;
	double		surfout;
	int			res;
	t_point		vect1;
	t_point		vect2;
	double		delta1;
	double		delta2;
	t_plane2	bot;
	t_plane2	top;

	cyl = (t_cylinder *)data;
	res = intersect_cylinder2(pos_start, vect_start, cyl->pos, cyl->vect,
		cyl->rad, &in, &out);
	bot.a = -cyl->vect.x;
	bot.b = -cyl->vect.y;
	bot.c = -cyl->vect.z;
	bot.d = cyl->vect.x * cyl->pos.x + cyl->vect.y * cyl->pos.y + cyl->vect.z * cyl->pos.z;
	top.a = cyl->vect.x;
	top.b = cyl->vect.y;
	top.c = cyl->vect.z;
	top.d = -cyl->vect.x * cyl->pos2.x - cyl->vect.y * cyl->pos2.y - cyl->vect.z * cyl->pos2.z;
	res = res && clipobj(&pos_start, &vect_start, &bot, &top, &in, &out, &surfin, &surfout);
	*intersection_pos = vector_new(
		pos_start.x + (vect_start.x * in),
		pos_start.y + (vect_start.y * in),
		pos_start.z + (vect_start.z * in));
	return (res);
}

int
	get_color_cylinder
	(void *data,
	t_point intersection_pos)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)data;
	return (cylinder->color);
}

t_point
	get_normal_cylinder
	(void *data,
	t_point intersection_pos)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)data;
	return (cylinder->vect);
}

void
	objects_add_cylinder
	(t_data *data,
	t_cylinder *cylinder)
{
	t_obj3d	**objects;
	int		index;

	data->mydata->objects_count++;
	objects =
	(t_obj3d **)malloc(sizeof(t_obj3d *) * data->mydata->objects_count);
	index = -1;
	while (++index < (data->mydata->objects_count - 1))
		objects[index] = data->mydata->objects[index];
	objects[index] = (t_obj3d *)malloc(sizeof(t_obj3d));
	objects[index]->data = cylinder;
	objects[index]->intersect = intersect_cylinder;
	objects[index]->get_color = get_color_cylinder;
	objects[index]->get_normal_vector = get_normal_cylinder;
	if (data->mydata->objects_count > 1)
		free(data->mydata->objects);
	data->mydata->objects = objects;
}
