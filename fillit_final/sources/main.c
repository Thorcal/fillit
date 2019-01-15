/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 11:36:29 by vrobin            #+#    #+#             */
/*   Updated: 2019/01/15 11:41:14 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		main(int argc, char **argv)
{
	int fd;

	if (argc == 2)
	{
		ft_putstr("Reading ");
		ft_putendl(argv[1]);
		fd = open(argv[1], O_RDONLY);
		if (print_tile(fd) == -1)
			ft_putendl("error");
	}
	else
		ft_putendl("usage ./fillit source_file");
}
