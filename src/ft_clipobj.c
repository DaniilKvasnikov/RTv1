/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clipobj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 15:00:33 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/03/20 15:00:48 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

int
	clipobj2
	(t_clipobj2 o)
{
	if (o.dc != 0.0)
	{
		o.t = -o.dw / o.dc;
		if (o.dc >= 0.0)
		{
			if (o.t > o.in && o.t < o.out)
			{
				o.out = o.t;
				*o.surfout = o.new_;
			}
			if (o.t < o.in)
				return (0);
		}
		else
		{
			if (o.t > o.in && o.t < o.out)
			{
				o.in = o.t;
				*o.surfin = o.new_;
			}
			if (o.t > o.out)
				return (0);
		}
	}
	return (1);
}

int
	clipobj
	(t_clipobj o)
{
	double	dc;
	double	dw;
	double	in;
	double	out;

	*o.surfin = 0;
	*o.surfout = 0;
	in = *o.objin;
	out = *o.objout;
	dc = o.bot->a * o.rayc->x + o.bot->b * o.rayc->y + o.bot->c * o.rayc->z;
	dw = o.bot->a * o.raybase->x + o.bot->b * o.raybase->y +
	o.bot->c * o.raybase->z + o.bot->d;
	if ((dc == 0.0 && dw >= 0.0) ||
	(clipobj2((t_clipobj2){dc, dw, 0, in, out, o.surfout, o.surfin, 1}) == 0))
		return (0);
	dc = o.top->a * o.rayc->x + o.top->b * o.rayc->y + o.top->c * o.rayc->z;
	dw = o.top->a * o.raybase->x + o.top->b * o.raybase->y +
	o.top->c * o.raybase->z + o.top->d;
	if ((dc == 0.0 && dw >= 0.0) ||
		clipobj2((t_clipobj2){dc, dw, 0, in, out, o.surfout, o.surfin, 2}) == 0)
		return (0);
	*o.objin = in;
	*o.objout = out;
	return (in < out);
}
