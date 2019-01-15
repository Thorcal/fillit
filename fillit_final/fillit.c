/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 11:01:13 by vrobin            #+#    #+#             */
/*   Updated: 2019/01/15 14:15:15 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	**move_up(char **tile, char **temp, int x, int y)
{
	while (tile[0][0] == '.' && tile[0][1] == '.' && tile[0][2] == '.'
			&& tile[0][3] == '.')
	{
		x = 0;
		while (x < 4)
		{
			y = 0;
			while (y < 3)
			{
				tile[y][x] = temp[y + 1][x];
				y++;
			}
			tile[y][x] = '.';
			x++;
		}
	}
	return (tile);
}

char	**move_upper_left(char **tile)
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

char	**fill_piece(char *buffer)
{
	int			x;
	int			y;
	char		**piece_tab;
	static int	i = 0;
	static char	character = '@';

	character += 1;
	if (!(piece_tab = (char**)malloc(sizeof(char*) * 3)))
		return (NULL);
	piece_tab[3] = NULL;
	y = 0;
	while (y < 4)
	{
		if (!(piece_tab[y] = ft_strnew(4)))
			return (NULL);
		x = 0;
		while (x < 4)
		{
			if (buffer[i] == '#')
				piece_tab[y][x++] = character;
			else
				piece_tab[y][x++] = buffer[i];
			i++;
		}
		y++;
		i++;
	}
	i++;
	move_upper_left(piece_tab);
	return (piece_tab);
}

int		print_tile(fd)
{
	int		i;
	int		tiles;
	int		size;
	char	*buffer;
	char	**grid;
	char	***test;

	if (!(buffer = ft_strnew(BUFF_SIZE + 1)))
		return (-1);
	i = read(fd, buffer, BUFF_SIZE);
	if ((tiles = is_valid(buffer, i)) == -1)
		return (-1);
	if (!(test = (char***)malloc(sizeof(char**) * tiles + 1)))
		return (-1);
	test[tiles] = NULL;
	i = 0;
	while (i < tiles)
	{
		if (!(test[i] = (char**)malloc(sizeof(char*) * 4)))
			return (-1);
		test[i][4] = NULL;
		test[i] = fill_piece(buffer);
		if (get_connections(test[i]) != 1)
			return (-1);
		i++;
	}
	size = high_sqrt(tiles * 4);
	grid = create_grid(size);
	while (place_tiles(tiles, grid, size, test, 0) != 1)
	{
		size += 1;
		ft_memdel((void**)grid);
		grid = create_grid(size);
	}
	free(test);
	free(buffer);
	return (0);
}
