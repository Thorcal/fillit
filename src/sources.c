/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sources.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 14:12:38 by vrobin            #+#    #+#             */
/*   Updated: 2019/02/05 14:46:14 by spuisais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fillit.h"

int		get_size(int tiles)
{
	static int	size;

	if (tiles == -1)
		return (size += 1);
	if (tiles == 0)
		return (size);
	else
		size = high_sqrt(tiles * 4);
	return (size);
}

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

void	free_blocs_grid(char ****blocs, char ***grid, int tiles)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < tiles)
	{
		while (j < 4)
		{
			free((*blocs)[i][j]);
			j++;
		}
		j = 0;
		free((*blocs)[i]);
		i++;
	}
	i = 0;
	while (i < get_size(0))
	{
		free((*grid)[i]);
		i++;
	}
	free(*blocs);
	free(*grid);
}
