/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 12:35:19 by vrobin            #+#    #+#             */
/*   Updated: 2019/02/05 17:19:36 by spuisais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fillit.h"

static char		**move_upper_left(char **tile)
{
	int		x;
	int		y;
	char	**temp;

	temp = tile;
	while (tile[0][0] == '.' && tile[1][0] == '.' && tile[2][0] == '.'
			&& tile[3][0] == '.')
	{
		y = 0;
		while (y < 4)
		{
			x = 0;
			while (x < 3)
			{
				tile[y][x] = temp[y][x + 1];
				x++;
			}
			tile[y][x] = '.';
			y++;
		}
	}
	tile = move_up(tile, temp, x, y);
	return (tile);
}

static int		put_char(char ***piece_tab,
		char **buffer, char character, int *i)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (y < 4)
	{
		if (!((*piece_tab)[y] = ft_strnew(4)))
			return (-1);
		x = 0;
		while (x < 4)
		{
			if ((*buffer)[*i] == '#')
				(*piece_tab)[y][x++] = character;
			else
				(*piece_tab)[y][x++] = (*buffer)[*i];
			(*i)++;
		}
		y++;
		(*i)++;
	}
	(*i)++;
	return (0);
}

static char		**fill_piece(char *buffer)
{
	char		**piece_tab;
	static int	i = 0;
	static char	character = '@';

	character += 1;
	if (!(piece_tab = (char**)malloc(sizeof(char*) * 3)))
		return (NULL);
	piece_tab[3] = NULL;
	put_char(&piece_tab, &buffer, character, &i);
	move_upper_left(piece_tab);
	return (piece_tab);
}

static int		loop(char ****blocs, int tiles, char **buffer)
{
	int	i;

	i = 0;
	while (i < tiles)
	{
		(*blocs)[i] = fill_piece(*buffer);
		if (get_connections((*blocs)[i]) != 1)
			return (-1);
		i++;
	}
	return (0);
}

int				print_tile(int fd)
{
	int		i;
	int		tiles;
	char	*buffer;
	char	**grid;
	char	***blocs;

	if (!(buffer = ft_strnew(BUFF_SIZE + 1)))
		return (-1);
	i = read(fd, buffer, BUFF_SIZE);
	if ((tiles = is_valid(buffer, i)) == -1)
		return (-1);
	if (!(blocs = (char***)malloc(sizeof(char**) * tiles)))
		return (-1);
	blocs[tiles] = NULL;
	if (tiles > 26 || loop(&blocs, tiles, &buffer) == -1)
		return (-1);
	grid = create_grid(get_size(tiles));
	while (place_tiles(tiles, grid, blocs, 0) != 1)
	{
		free(grid);
		grid = create_grid(get_size(-1));
	}
	free_blocs_grid(&blocs, &grid, tiles);
	free(buffer);
	return (0);
}
