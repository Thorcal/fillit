/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fillit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuisais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 11:17:22 by spuisais          #+#    #+#             */
/*   Updated: 2019/01/10 13:27:38 by spuisais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "libft/get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

void	osef(char **tab, int size);

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

void	place_tile(char **tab, char **tile, int y, int x)
{
	int tilex;
	int tiley;

	tiley = 0;
	while (tiley < 4)
	{
		tilex = 0;
		while (tilex < 4)
		{
			if (tile[tiley][tilex] != '.')
				tab[y + tiley][x + tilex] = tile[tiley][tilex];
			tilex++;
		}
		tiley++;
	}
}

int		check_spot(char **tab, char **tile, int y, int x, int size)
{
	int tilex;
	int tiley;
	int ok;

	tiley = 0;
	ok = 0;
	while (tiley < 4 && y + tiley < size)
	{
		tilex = 0;
		while (tilex < 4 && x + tilex < size)
		{
			if (tab[y + tiley][x + tilex] == '.' && tile[tiley][tilex] != '.')
				ok++;
			tilex++;
		}
		tiley++;
	}
	if (ok == 4)
		return (1);
	return (0);
}

void	osef(char **tab, int size)
{
	int i = 0;

	while (i < size)
	{
		ft_putstr(tab[i]);
		ft_putchar('\n');
		i++;
	}
}

int		place_tiles(int tiles, char **tab, int size, char ***tile, int current)
{
	int	x;
	int	y;

	y = 0;
	if (current == tiles)
	{
		osef(tab, size);
		return (1);
	}
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (check_spot(tab, tile[current], y, x, size) == 1)
			{
				place_tile(tab, tile[current], y, x);
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

char	**create_grid(int tiles, int *size)
{
	static int	gridSize;
	char		**tab;
	int			i;
	int			j;

	i = 1;
	if (gridSize == 0)
	{
		while (i * i < (tiles * 4))
			i++;
		gridSize = i;
	}
	else
		gridSize += 1;
	*size = gridSize;
	if (!(tab = (char**)malloc(sizeof(char*) * gridSize)))
		return (NULL);
	i = 0;
	while (i < gridSize)
	{
		if (!(tab[i] = (char*)malloc(sizeof(char) * gridSize)))
			return (NULL);
		i++;
	}
	i = 0;
	while (i < *size)
	{
		j = 0;
		while (j < *size)
		{
			tab[i][j] = '.';
			j++;
		}
		i++;
	}
	return (tab);
}

char	**move_upper_left(char **tile)
{
	int		y;
	int		x;
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

int		count_connections(char **tile, int y, int x)
{
	int count;
	
	count = 0;
	if (y - 1 != -1 && tile[y - 1][x] != '.')
		count++;
	if (y + 1 != 4 && tile[y + 1][x] != '.')
		count++;
	if (x - 1 != -1 && tile[y][x - 1] != '.')
		count++;
	if (x + 1 != 4 && tile[y][x + 1] != '.')
		count++;
	return (count);
}

int		get_connections(char **tile)
{
	int connections;
	int y;
	int x;

	connections = 0;
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (tile[y][x] != '.')
				connections += count_connections(tile, y, x);
			x++;
		}
		y++;
	}
	if (connections == 6 || connections == 8)
		return (1);
	return (0);
}

char	**fill_piece(char *buffer)
{
	static char	character;
	static int	i;
	int			x;
	int			y;
	char		**piece_tab;

	if (!character)
		character = 'A';
	else
		character += 1;
	if (!(piece_tab = (char**)malloc(sizeof(char*) * 4)))
		return (NULL);
	y = 0;
	while (y < 4)
	{
		if (!(piece_tab[y] = (char*)malloc(sizeof(char) * 4)))
			return (NULL);
		x = 0;
		while (x < 4)
		{
			if (buffer[i] == '#')
				piece_tab[y][x] = character;
			else
				piece_tab[y][x] = buffer[i];
			x++;
			i++;
		}
		y++;
		i++;
	}
	i++;
	move_upper_left(piece_tab);
	return (piece_tab);
}

//check la validite du buffer et renvoie le nombre de tetriminos trouves ou -1 si erreur
int		is_valid(char *buffer, int buflen)
{
	int len;
	int i;
	int lnum;
	int blocs;

	i = 0;
	lnum = 1;
	blocs = 0;
	while (i < buflen)
	{
		len = 0;
		while (buffer[i] != '\n' && buffer[i] != '\0')
		{
			if (buffer[i] == '#')
				blocs++;
			i++;
			len++;
		}
		if ((lnum % 5 == 0 && len != 0) || (lnum % 5 == 0 && blocs != 4)
			   	|| (lnum % 5 != 0 && len != 4))
			return (-1);
		if (lnum % 5 == 0)
			blocs = 0;
		lnum++;
		i++;
	}
	return ((lnum + 1) / 5);
}

//rempli le buffer grace au fd
int		print_tile(fd)
{
	int		i;
	int		j;
	int		tiles;
	int		size;
	char	*buffer;
	char 	***test;
	char	**grid;

	j = 0;
	if (!(buffer = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1))) || 
			!(test = (char***)malloc(sizeof(char**) * 3)))
		return (-1);
	i = read(fd, buffer, BUFF_SIZE);
	if ((tiles = is_valid(buffer, i)) == -1)
		return (-1);
	while (j < tiles)
	{
		if (!(test[j] = (char**)malloc(sizeof(char*) * 4)))
			return (-1);
		test[j] = fill_piece(buffer);
		if (get_connections(test[j]) != 1)
			return (-1);
		j++;
	}
	grid = create_grid(tiles, &size);
	if (place_tiles(tiles, grid, size, test, 0) == 1)
		return (1);
	grid = create_grid(tiles, &size);
	if (place_tiles(tiles, grid, size, test, 0) == 1)
		return (1);
	grid = create_grid(tiles, &size);
	if (place_tiles(tiles, grid, size, test, 0) == 1)
		return (1);
	return (0);
}

int		main(int argc, char *argv[])
{
	int	fd;

	if (argc == 2)
	{
		printf("Reading \"%s\".\n", argv[1]);
		fd = open(argv[1], O_RDONLY);
		if (print_tile(fd) == -1)
			ft_putstr("Erreur.\n");
	}
	else
		ft_putstr("usage: ./fillit source_file");
}
