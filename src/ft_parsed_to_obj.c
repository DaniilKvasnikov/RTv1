#include "main.h"

void		ft_add_light(t_data **data, t_parsed *p)
{
	t_data *list;
	int		*i;

	list = *data;
	i = &list->mydata->light_num;
	if (p)
	{
		list->mydata->light[*i] = p->pos;
		*i += 1;
	}
}

void ft_init_lights(t_data **data)
{
	t_data *list;

	list = *data;
	list->mydata->light =
	(t_point *)malloc(sizeof(t_point) * (list->mydata->light_count) + 1);
	list->mydata->light->x = 10;
	list->mydata->light->y = 0;
	list->mydata->light->z = 0;
	list->mydata->light_num++;
}

void ft_parse_lights(t_data **data)
{
	t_data *list;
	t_parsed *parsed;

	list = *data;
	ft_init_lights(data);
	parsed = list->mydata->parsed_obj;
	while (parsed)
	{
		if (parsed->type == 5)
			ft_add_light(data, parsed);
		parsed = parsed->next;
	}
}

void ft_add_obj(t_data **data, t_parsed *p)
{
	t_data *list;

	list = *data;
	if (p->type == 1)
		objects_add_sphere(
			list,
			new_sphere(p->pos, p->rad, p->color));
	if (p->type == 2)
		objects_add_cylinder(
			list,
			new_cylinder(p->pos, p->vect, p->h, p->rad, p->color));
	if (p->type == 3)
		objects_add_triangle(
			list,
			new_triangle(p->p1, p->p2, p->p3, p->color));
}

void ft_parsed_to_obj(t_data **data)
{
	t_data *list;
	t_parsed *parsed;

	list = *data;
	parsed = list->mydata->parsed_obj;
	while (parsed)
	{
		ft_add_obj(data, parsed);
		parsed = parsed->next;
	}
}
