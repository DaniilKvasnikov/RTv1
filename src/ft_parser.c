#include "main.h"

void		ft_parse_error(char *msg)
{
	ft_printf("PARSE ERROR : ");
	if (msg)
		ft_printf("%s\n", msg);
	exit(0);
}

void ft_parser(t_data **data)
{
	char *input;
	char *content;
	char *p;
	char *name;
	t_data *list;

	list = *data;
	ft_read_file(list->mydata);
	input = list->mydata->input;
	name = NULL;
	p = NULL;
	while ((content = ft_get_info(input, &p, &name, 0)))
	{
		input = p;
		if (!*content)
			break;
		ft_add_object(list->mydata, name, content);
		ft_strdel(&name);
		ft_strdel(&content);
	}
	if (content != NULL)
		ft_parse_error("Invalid file");
	/* пока lights вносится сразу, объекты хранятся в parsed
	доработать: добавлять объекты сразу в obj3d */
}
