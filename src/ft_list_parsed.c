#include "main.h"

t_parsed	*new_obj(void)
{
	t_parsed *new;

	new = (t_parsed *)ft_memalloc(sizeof(t_parsed));
	new->type = 1;
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
	else if (ft_strequ(name, "plane"))
		return (3);
	else if (ft_strequ(name, "triangle"))
		return (4);
	else if (ft_strequ(name, "light"))
		return (5);
	return (0);
}

void		ft_add_light(t_mydata *mydata, char *content)
{
	t_parsed	*cur;
	char		*str;

	str = get_content(content, 1);
	cur = mydata->parsed_obj;
	if (cur)
	{
		mydata->light[mydata->light_count] = ft_get_vector(str);
		mydata->light_count++;
	}
}

void		ft_add_object(t_mydata *mydata, char *name, char *content)
{
	t_parsed *obj;
	int type;

	if ((type = ft_is_obj(name)))
	{
		obj = new_obj();
		obj->type = type;
		ft_parse_object(&obj, content);
		obj_push_back(&mydata->parsed_obj, obj);
	}
	else if (ft_strequ(name, "light"))
	{
	//	ft_add_light(mydata, content);
	}
	/* else
		ft_parse_error("Error object"); */
}
