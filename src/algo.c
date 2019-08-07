/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 11:57:35 by vrobin            #+#    #+#             */
/*   Updated: 2019/02/05 14:59:32 by spuisais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fillit.h"

char			**create_grid(int size)
{
	char	**tab;
	int		i;
	int		j;

	j = 0;
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
	j = 0;
	return (tab);
}

static void		put_tile(char **tab, char **tile, int x, int y)
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

static void		clear(char **tab, int size, int current)
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

static int		check_aff(int current, int tiles, char **tab)
{
	int i;

	i = 0;
	if (current == tiles)
	{
		while (i < get_size(0))
			ft_putendl(tab[i++]);
		return (1);
	}
	return (0);
}

int				place_tiles(int tiles, char **tab, char ***tile, int current)
{
	int	x;
	int	y;

	y = 0;
	if (check_aff(current, tiles, tab) == 1)
		return (1);
	while (y < get_size(0))
	{
		x = 0;
		while (x < get_size(0))
		{
			if (check_spot(tab, tile[current], x, y) == 1)
			{
				put_tile(tab, tile[current], x, y);
				if (place_tiles(tiles, tab, tile, current + 1) == 1)
					return (1);
				else
					clear(tab, get_size(0), current);
			}
			x++;
		}
		y++;
	}
	return (0);
}
