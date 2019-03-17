#include "main.h"

t_parsed	*new_obj(void)
{
	t_parsed *new;

	new = (t_parsed *)ft_memalloc(sizeof(t_parsed));
	new->type = 1;
	new->p1 = vector_new(-1.5, -1.5, 10.5);
	new->p2 = vector_new(-1.5, 1.5, 10.5);
	new->p3 = vector_new(1.5, -1.5, 10.5);
	new->pos = vector_new(0, 0, 10);
	new->vect = vector_new(0.5, 0.5, 0);
	new->rad = 2;
	new->h = 20;
	new->next = NULL;
	new->color = RGB_RED;
	return (new);
}

void		obj_push_back(t_parsed **list, t_parsed *cur)
{
	if (!list)
		return;
	while (*list)
		list = &(*list)->next;
	*list = cur;
}

int			ft_is_obj(char *name)
{
	if (ft_strequ(name, "sphere"))
		return (1);
	else if (ft_strequ(name, "cylinder"))
		return (2);
	else if (ft_strequ(name, "triangle"))
		return (3);
	else if (ft_strequ(name, "plane"))
		return (4);
	else if (ft_strequ(name, "light"))
		return (5);
	else if (ft_strequ(name, "cam"))
		return (6);
	return (0);
}

void		ft_add_object(t_mydata *mydata, char *name, char *content)
{
	t_parsed *obj;
	int type;

	if ((type = ft_is_obj(name)))
	{
		obj = new_obj();
		obj->type = type;
		type == 5 ? mydata->light_count += 1 : 0;
		ft_parse_object(&obj, content);
		obj_push_back(&mydata->parsed_obj, obj);
	}
/* 	else if (ft_strequ(name, "light"))
	{
		ft_add_light(mydata, content);
	} */
	/* else
		ft_parse_error("Error object"); */
}
