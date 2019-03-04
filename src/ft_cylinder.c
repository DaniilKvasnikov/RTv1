/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 18:15:14 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/02 16:06:51 by rrhaenys         ###   ########.fr       */
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
	cylinder->rad = rad;
	cylinder->color = color;
	return (cylinder);
}
/* ---- intcyl - Пересечь луч с цилиндром. --------------------- */
/* */
/* */
/*	Описание:							*/
/* Intcyl определяет пересечение луча с */
/* цилиндр. */
/* */
/* На входе: */
/* raybase = базовая точка пересекающегося луча. */
/* raycos = Направляющие косинусы вышеупомянутого луча. (единица измерения)	*/
/* base = Базовое местоположение цилиндра. */
/* ось = ось симметрии для цилиндра. (единица измерения)	*/
/* radius = радиус цилиндра. */
/* */
/* По возвращении: */
/* in = Входное расстояние пересечения. */
/* out = расстояние до пересечения. */
/* */
/* Returns: True, если луч пересекает цилиндр. */
/* */
/* Примечание: вход и / или выход может быть отрицательным, указывая */
/* цилиндр расположен за началом луча. */
/* */
/* ------------------------------------------------ -------------------- */
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
    int			hit;	/* True if ray intersects cyl   */
    t_point		RC;		/* Ray base to cylinder base    */
    double		d;		/* Shortest distance between    */
						/*   the ray and the cylinder   */
    double		t;
	double		s;		/* Distances along the ray  */
    t_point		n;
	t_point		D;
	t_point		O;
    double		ln;
	const double	pinf = HUGE;    /* Positive infinity        */

	RC = vector_new(raybase.x - base.x, raybase.y - base.y, raybase.z - base.z);
    n = cross_product(raycos,axis);

    if  ( (ln = module_vector(&n)) == 0 ) {    /* ray parallel to cyl  */
        d    = vector_sum(&RC,&axis);
		D = vector_new(RC.x - d*axis.x, RC.y - d*axis.y, RC.z - d*axis.z);
        d    = module_vector(&D);
        *in  = -pinf;
        *out =  pinf;
        return (d <= radius);       /* true if ray is in cyl*/
    }
	vector_normalize(&n);

    d    = fabs(vector_sum(&RC,&n));      /* shortest distance    */
    hit  = (d <= radius);
    if  (hit) {             /* if ray hits cylinder */
        O = cross_product(RC,axis);
        t = - vector_sum(&O,&n) / ln;
        O = cross_product(n,axis);
		vector_normalize(&O);
        s = fabs (sqrt(radius*radius - d*d) / vector_sum(&raycos,&O));
        *in  = t - s;           /* entering distance    */
        *out = t + s;           /* exiting  distance    */
    }

    return (hit);
}

void
	ft_printf_vect
	(t_point *p,
	char *s)
{
//	printf("%s %lf %lf %lf\n", s, p->x, p->y, p->z);
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
	int			res;

	cyl = (t_cylinder *)data;
	res = 0;
	ft_printf_vect(&cyl->vect, "cyl->vect");
	res = intersect_cylinder2(pos_start, vect_start, cyl->pos, cyl->vect, cyl->rad, &in, &out);
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
