/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 11:57:35 by vrobin            #+#    #+#             */
/*   Updated: 2019/01/21 10:32:10 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	**create_grid(int size)
{
	char	**tab;
	char	**tmp;
	int		i;
	int		j;

	j = 0;
	tmp = NULL;
	i = size;
	if (!(tab = (char**)malloc(sizeof(char*) * size)))
		return (NULL);
	tab[size] = NULL;
	while (j < size)
		if (!(tab[j++] = ft_strnew(size)))
			return (NULL);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
			tab[i][j++] = '.';
		i++;
	}
	tmp = tab;
	free(tab);
	return (tmp);
}

void	put_tile(char **tab, char **tile, int x, int y)
{
	int tile_x;
	int tile_y;

	tile_y = 0;
	while (tile_y < 4)
	{
		tile_x = 0;
		while (tile_x < 4)
		{
			if (tile[tile_y][tile_x] != '.')
				tab[y + tile_y][x + tile_x] = tile[tile_y][tile_x];
			tile_x++;
		}
		tile_y++;
	}
}

void	clear(char **tab, int size, int current)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (tab[i][j] == 'A' + current)
				tab[i][j] = '.';
			j++;
		}
		i++;
	}
}

int		check_aff(int current, int tiles, int size, char **tab)
{
	if (current == tiles)
	{
		aff_tetro(tab, size);
		return (1);
	}
	return (0);
}

int		place_tiles(int tiles, char **tab, int size, char ***tile, int current)
{
	int	x;
	int	y;

	y = 0;
	if (check_aff(current, tiles, size, tab) == 1)
		return (1);
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (check_spot(tab, tile[current], x, y, size) == 1)
			{
				put_tile(tab, tile[current], x, y);
				if (place_tiles(tiles, tab, size, tile, current + 1) == 1)
					return (1);
				else
					clear(tab, size, current);
			}
			x++;
		}
		y++;
	}
	return (0);
}
