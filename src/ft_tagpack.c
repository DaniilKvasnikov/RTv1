#include "main.h"

t_point		ft_get_vector(char *value)
{
	double x;
	double y;
	double z;
	char **tab;

	tab = ft_strsplit(value, ',');
	x = ft_atof(tab[0]);
	y = ft_atof(tab[1]);
	z = ft_atof(tab[2]);
	return (vector_new(x, y, z));
}

void		tags_pack(t_parsed **obj3, char *tag, char *content)
{
	t_parsed *obj;

	obj = *obj3;
	if (ft_strequ(tag, "rad"))
		obj->rad = ft_atof(content);
	else if (ft_strequ(tag, "pos"))
		obj->pos = ft_get_vector(content);
	else if (ft_strequ(tag, "color"))
		obj->color = ft_atoh(content);
	else if (ft_strequ(tag, "vect"))
		obj->vect = ft_get_vector(content);
	else if (ft_strequ(tag, "h"))
		obj->h = ft_atoi(content);
}

void		ft_parse_object(t_parsed **obj, char *line)
{
	char *input;
	char *content;
	char *ptr;
	char *tag;

	input = line;
	tag = NULL;
	content = NULL;
	while ((content = ft_get_info(input, &ptr, &tag, 1)))
	{
		input = ptr;
		if (!*content)
			break;
		tags_pack(obj, tag, content);
		ft_strdel(&tag);
		ft_strdel(&content);
	}
}
