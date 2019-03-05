#include "main.h"

void ft_parse_error(char *msg)
{
	ft_printf("PARSE ERROR : ");
	if (msg)
		ft_printf("%s\n", msg);
	exit(0);
}

void ft_remove_tabs(char **str)
{
	int i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\t' || (*str)[i] == ' ')
			ft_memcpy(*str + i, *str + i + 1, ft_strlen(*str + i));
		else
			i++;
	}
}

void ft_read_file(t_mydata *mydata)
{
	char *line;
	int fd;
	int ret;

	line = NULL;
	fd = open(mydata->argv[0], O_RDONLY);
	if (fd == -1)
		return;
	mydata->input = ft_strdup("");
	while ((ret = get_next_line(fd, &line) > 0))
	{
		mydata->input = ft_strjoin(mydata->input, ft_strdup(line));
		ft_strdel(&line);
	}
	ft_remove_tabs(&mydata->input);
	if (ret != 0)
		return;
	close(fd);
}

t_parsed *new_obj(void)
{

	t_parsed *new;

	new = (t_parsed *)ft_memalloc(sizeof(t_parsed));
	new->type = 1;
	new->pos = vector_new(0, 0, 10);
	new->rad = 1;
	new->color = RGB_RED;
	new->next = NULL;
	return (new);
}

void obj_push_back(t_parsed  **list, t_parsed *cur)
{
	if (!list)
		return;
	while (*list)
		list = &(*list)->next;
	*list = cur;
}

void tags_pack(t_parsed *obj, char *tag, char *content)
{
	if (ft_strequ(tag, "rad"))
		obj->type = ft_atoi(content);
}



void	ft_parse_object(t_parsed *obj, char *line)
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
			break ;
		tags_pack(obj, tag, content);
		ft_strdel(&tag);
		ft_strdel(&content);
	}
}

void ft_add_object(t_mydata *mydata, char *name, char *content)
{
	t_parsed *obj;

	if (ft_strequ(name, "sphere"))
	{
		obj = new_obj();
		ft_parse_object(obj, content);
		obj_push_back(&mydata->parsed_obj, obj);
	}
	/* else if (ft_strequ(name, "light"))
	{

	} */
	/* else
		ft_parse_error("Unknown object !"); */
}

void ft_parser(t_mydata *mydata)
{
	char *input;
	char *content;
	char *p;
	char *name;

	ft_read_file(mydata);
	input = mydata->input;
	name = NULL;
	p = NULL;
	while ((content = ft_get_info(input, &p, &name, 0)))
	{
		input = p;
		if (!*content)
			break;
		ft_add_object(mydata, name, content);
		ft_strdel(&name);
		ft_strdel(&content);
	}
	if (content != NULL)
		ft_parse_error("Invalid file");
	/* добавить вставку объектов на основе name и content */
}
