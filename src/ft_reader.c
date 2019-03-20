/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 21:03:28 by jfrankly          #+#    #+#             */
/*   Updated: 2019/03/19 21:03:29 by jfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_remove_tabs(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\t' || (*str)[i] == ' ')
			ft_memcpy(*str + i, *str + i + 1, ft_strlen(*str + i));
		else
			i++;
	}
}

void	ft_read_file(t_mydata *mydata)
{
	char	*line;
	int		fd;
	int		ret;

	line = NULL;
	if (!(fd = open(mydata->argv[0], O_RDONLY)))
		ft_parse_error("opening error");
	if (fd == -1)
		ft_parse_error("ivalid file");
	mydata->input = ft_strdup("");
	while ((ret = get_next_line(fd, &line) > 0))
	{
		mydata->input = ft_strjoin(mydata->input, ft_strdup(line));
		ft_strdel(&line);
	}
	ft_remove_tabs(&mydata->input);
	if (ret != 0)
		return ;
	close(fd);
}
