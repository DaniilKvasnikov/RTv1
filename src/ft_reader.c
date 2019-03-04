#include "main.h"

void	ft_parse_error(char *msg)
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
	while ((content = ft_get_info(input, &p, &name)))
	{
		input = p;
		if (!*content)
			break;
		ft_strdel(&name);
		ft_strdel(&content);
	}
	 if (content != NULL)
		ft_parse_error("Invalid file");
	/* добавить вставку объектов на основе name и content */
}
