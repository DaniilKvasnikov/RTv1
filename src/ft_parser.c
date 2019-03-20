/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 21:01:00 by jfrankly          #+#    #+#             */
/*   Updated: 2019/03/19 21:01:01 by jfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		ft_correct_fd(int argc, char **argv)
{
	int		fd;

	if (!(fd = open(argv[0], O_RDONLY)))
		ft_parse_error("opening error");
	if (fd == -1 || (argc == 2 && !ft_strequ(argv[1], "-k")))
		ft_parse_error("ivalid file");
	return (fd);
}

void		ft_parse_error(char *msg)
{
	ft_printf("ERROR : ");
	if (msg)
		ft_printf("%s\n", msg);
	exit(0);
}

void		ft_parser(t_data **data)
{
	char	*input;
	char	*content;
	char	*p;
	char	*name;
	t_data	*list;

	list = *data;
	ft_read_file(list->mydata);
	input = list->mydata->input;
	name = NULL;
	p = NULL;
	while ((content = ft_get_info(input, &p, &name, 0)))
	{
		input = p;
		if (!*content)
			break ;
		ft_create_and_add_object(list->mydata, name, content);
		ft_strdel(&name);
		ft_strdel(&content);
	}
	if (content != NULL)
		ft_parse_error("Invalid file");
}
