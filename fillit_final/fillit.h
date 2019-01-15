/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 10:58:45 by vrobin            #+#    #+#             */
/*   Updated: 2019/01/15 12:30:52 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include "libft/get_next_line.h"
# include "libft/libft.h"
# include "fcntl.h"

int		print_tile(int fd);
int		main(int argc, char **argv);
int		is_valid(char *buffer, int buflen);
int		get_connections(char **tile);
int		place_tiles(int tiles, char **tab, int size, char ***tile, int current);
char	**create_grid(int size);
int		check_spot(char **tab, char **tile, int x, int y, int size);
void	aff_tetro(char	**tab, int size);
#endif
