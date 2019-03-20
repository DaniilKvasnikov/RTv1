/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsed_to_obj.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 21:00:54 by jfrankly          #+#    #+#             */
/*   Updated: 2019/03/19 21:00:56 by jfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_add_cam(t_data *data, t_point pos, t_point angle)
{
	data->mydata->pos = pos;
	data->mydata->angle = angle;
}

void	ft_add_obj(t_data **data, t_parsed *p)
{
	t_data *list;

	list = *data;
	if (p->type == 1)
		objects_add_sphere(list, new_sphere(p->pos, p->rad, p->color));
	if (p->type == 2)
		objects_add_cylinder(list,
			new_cylinder(p->pos, p->vect, vector_new(p->h, p->rad, 0), p->color));
	if (p->type == 3)
		objects_add_triangle(list,
			new_triangle(p->p1, p->p2, p->p3, p->color));
	if (p->type == 4)
		objects_add_cone(list,
			new_cone(p->pos, p->vect, p->rad, p->color));
	if (p->type == 5)
		ft_add_lights(list, p->pos, p->l_pow);
	if (p->type == 6)
		ft_add_cam(list, p->pos, p->vect);
	if (p->type == 7)
		objects_add_plane(
		list, new_plane(p->pos, p->vect, p->color));
}

void	ft_lstfree(t_parsed *alst)
{
	t_parsed	*tmp;

	tmp = alst;
	while (tmp)
	{
		alst = tmp;
		tmp = tmp->next;
		free(alst);
	}
}

void	ft_parsed_to_obj(t_data **data)
{
	t_data		*list;
	t_parsed	*parsed;

	list = *data;
	parsed = list->mydata->parsed_obj;
	while (parsed)
	{
		ft_add_obj(data, parsed);
		parsed = parsed->next;
	}
	ft_lstfree(list->mydata->parsed_obj);
}
