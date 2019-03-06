#include "main.h"

void		ft_add_obj(t_data **data, t_parsed *parsed)
{
	t_data	*list;

	list = *data;
	if (parsed->type == 1)
		 objects_add_sphere(
		list,
		new_sphere(
			parsed->pos,
			parsed->rad,
			parsed->color));
}

void		ft_parsed_to_obj(t_data **data)
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
}
