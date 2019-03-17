#include "main.h"

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
	if (p->type == 4)
		objects_add_cone(
			list,
			new_cone(
			p->pos,
			p->vect,
			p->rad,
			p->color));
	if (p->type == 5)
		ft_add_lights(
			list,
			p->pos.x, p->pos.y, p->pos.z, p->l_pow);
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
