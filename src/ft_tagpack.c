#include "main.h"

int		ft_count_chars(char *str, char c)
{
	int	i;

	i = 0;
	while(*str)
	{
		if (*str == c)
			i++;
		str++;
	}
	return (i);
}

t_point ft_get_vector(char *value)
{
	double x;
	double y;
	double z;
	char **tab;

	if(ft_count_chars(value, ',') != 2)
		ft_parse_error("vector have invalid number of params");
	tab = ft_strsplit(value, ',');
	x = ft_atof(tab[0]);
	y = ft_atof(tab[1]);
	z = ft_atof(tab[2]);
	return (vector_new(x, y, z));
}

void tags_pack(t_parsed **obj3, char *tag, char *content)
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
	else if (ft_strequ(tag, "p1"))
		obj->p1 = ft_get_vector(content);
	else if (ft_strequ(tag, "p2"))
		obj->p2 = ft_get_vector(content);
	else if (ft_strequ(tag, "p3"))
		obj->p3 = ft_get_vector(content);
	else if (ft_strequ(tag, "l_pow"))
		obj->l_pow = ft_atof(content);
	else
		ft_parse_error("invalid tag!");

}

void ft_parse_object(t_parsed **obj, char *line)
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
