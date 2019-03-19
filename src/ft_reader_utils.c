/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reader_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 21:01:10 by jfrankly          #+#    #+#             */
/*   Updated: 2019/03/19 21:01:12 by jfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char *ft_strndup(char *s, size_t len)
{
	char *dup;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s) - 1;
	dup = ft_strnew(len);
	ft_strncpy(dup, s, len);
	return (dup);
}

char *ft_get_close(char *str, char a)
{
	char *p;

	p = str;
	while (*p)
	{
		if (*p == a)
			return (p);
		p++;
	}
	return (NULL);
}

char *get_name(char *line, int type)
{
	char *p;
	char *op;
	char *clos;

	op = line;
	if (!type)
		clos = ft_get_close(op, '{');
	else if (type)
		clos = ft_get_close(op, ':');
 	if (!op || !clos)
		ft_parse_error("object name reading failed ");
	p = ft_strndup(op, clos - op);
	return (p);
}

char *get_content(char *line, int type)
{
	char *p;
	char *op;
	char *clos;

	p = line;
	if (!type)
	{
		op = ft_get_close(p, '{') + 1;
		clos = ft_get_close(op, '}');
	}
	else if (type)
	{
		op = ft_get_close(p, ':') + 1;
		clos = ft_get_close(op, ';');
	}
	if (!op || !clos)
		ft_parse_error("object parametres reading failed");
	p = ft_strndup(op, clos - op);
	return (p);
}

char *ft_get_info(char *line, char **p, char **name, int t)
{
	char *content;

	content = NULL;
	if (!line || !*line)
		return (NULL);
	*name = get_name(line, t);
	content = get_content(line, t);
	*p = line + ft_strlen(*name) + ft_strlen(content) + 2;
	return (content);
}
