/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_parsed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 20:33:14 by jfrankly          #+#    #+#             */
/*   Updated: 2019/03/19 20:33:18 by jfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_parsed	*new_obj(void)
{
	t_parsed *new;

	new = (t_parsed *)ft_memalloc(sizeof(t_parsed));
	new->type = 1;
	new->p1 = vector_new(-1.5, -1.5, 10.5);
	new->p2 = vector_new(-1.5, 1.5, 10.5);
	new->p3 = vector_new(1.5, 1.5, 10.5);
	new->pos = vector_new(0, 0, 0);
	new->vect = vector_new(0, 0, 0);
	new->rad = 2;
	new->h = 0;
	new->next = NULL;
	new->color = RGB_RED;
	new->l_pow = 0.2;
	return (new);
}

void		obj_push_back(t_parsed **list, t_parsed *cur)
{
	t_parsed	*tmp;

	tmp = NULL;
	if (list && cur)
	{
		tmp = *list;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = cur;
	}
}

int			ft_is_obj(char *name)
{
	if (ft_strequ(name, "sphere"))
		return (1);
	else if (ft_strequ(name, "cylinder"))
		return (2);
	else if (ft_strequ(name, "triangle"))
		return (3);
	else if (ft_strequ(name, "cone"))
		return (4);
	else if (ft_strequ(name, "light"))
		return (5);
	else if (ft_strequ(name, "cam"))
		return (6);
	else if (ft_strequ(name, "plane"))
		return (7);
	else
		ft_parse_error("invalid object type!");
	return (0);
}

void		ft_create_and_add_object(t_mydata *mydata,
				char *name, char *content)
{
	t_parsed	*obj;
	int			type;

	if ((type = ft_is_obj(name)))
	{
		obj = new_obj();
		obj->type = type;
		ft_parse_object(&obj, content);
		obj_push_back(&mydata->parsed_obj, obj);
	}
	else
		ft_parse_error("Error object");
}
