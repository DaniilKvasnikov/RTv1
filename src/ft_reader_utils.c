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

char *get_name(char *line)
{
	char *p;
	char *op;
	char *clos;

	op = line;
	clos = ft_get_close(op, '{');
	p = ft_strndup(op, clos - op);
	return (p);
}

char *get_content(char *line)
{
	char *p;
	char *op;
	char *clos;

	p = line;
	op = ft_get_close(p, '{') + 1;
	clos = ft_get_close(op, '}');
	p = ft_strndup(op, clos - op);
	return (p);
}

char *ft_get_info(char *line, char **p, char **name)
{
	char *content;

	content = NULL;
	if (!line || !*line)
		return (NULL);
	*name = get_name(line);
	content = get_content(line);
	*p = line + ft_strlen(*name) + ft_strlen(content) + 2;
	return (content);
}
