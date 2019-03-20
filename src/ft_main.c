/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 00:37:39 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/02/22 17:02:31 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int
	main
	(int argc,
	char **argv)
{
	int		fd;
	--argc;
	++argv;

	if (argc == 1 || argc == 2)
	{
		fd = ft_correct_fd(argc, argv);
		ft_open_win(argv[0], argc, argv, fd);
	}
	else
		ft_printf("%s\n",
		"./RTv1 [file_name]");
	return (0);
}
