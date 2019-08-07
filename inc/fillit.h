/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 10:58:45 by vrobin            #+#    #+#             */
/*   Updated: 2019/02/05 14:56:38 by spuisais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include "../libft/get_next_line.h"
# include "../libft/libft.h"
# include "fcntl.h"
# include <stdio.h>

void	free_blocs_grid(char ****blocs, char ***grid, int tiles);
char	**move_up(char **tile, char **temp, int x, int y);
void	aff_tetro(char	**tab, int size);
int		get_size(int tiles);
int		print_tile(int fd);
int		main(int argc, char **argv);
int		is_valid(char *buffer, int buflen);
int		get_connections(char **tile);
int		place_tiles(int tiles, char **tab, char ***tile, int current);
int		check_spot(char **tab, char **tile, int x, int y);
char	**create_grid(int size);
#endif
