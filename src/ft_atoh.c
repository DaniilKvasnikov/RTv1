/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 20:32:17 by jfrankly          #+#    #+#             */
/*   Updated: 2019/03/19 20:33:37 by jfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int				ft_notdigit(char *str)
{
	while (*str)
	{
		if (!(ft_isdigit(*str) || *str == '.' || *str == '-'))
			return (1);
		str++;
	}
	return (0);
}

unsigned int	ft_atoh(char *ap)
{
	char			*p;
	unsigned int	n;
	int				digit;
	int				lcase;

	p = ap;
	n = 0;
	while (*p == ' ' || *p == '	')
		p++;
	if (*p == '0' && ((*(p + 1) == 'x') || (*(p + 1) == 'X')))
		p += 2;
	while ((digit = (*p >= '0' && *p <= '9')) ||
			(lcase = (*p >= 'a' && *p <= 'f')) ||
			(*p >= 'A' && *p <= 'F'))
	{
		n *= 16;
		if (digit)
			n += *p++ - '0';
		else if (lcase)
			n += 10 + (*p++ - 'a');
		else
			n += 10 + (*p++ - 'A');
	}
	return (n);
}

float			ft_atof(const char *s)
{
	int		point[2];
	float	rez[2];

	point[0] = 0;
	rez[0] = 0;
	rez[1] = 1;
	if (ft_notdigit((char *)s))
		ft_parse_error("parametres values reading failed");	
	if (*s == '-')
	{
		s++;
		rez[1] = -1;
	}
	while (*s)
	{
		point[0] += (*s == '.')? 1 : 0;
/* 		if (*s == '.')
			point[0] = 1; */
		point[1] = *s - '0';
		if (point[1] >= 0 && point[1] <= 9)
		{
			/* if (point[0])
				rez[1] /= 10.0f; */
			rez[1] /= (point[0])? 10.0f : 1;
			rez[0] = rez[0] * 10.0f + (float)point[1];
		}
		s++;
	}
	return (rez[0] * rez[1]);
}
