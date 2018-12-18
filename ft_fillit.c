/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fillit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuisais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 11:17:22 by spuisais          #+#    #+#             */
/*   Updated: 2018/12/18 12:04:44 by spuisais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft/libft.h"
#include "libft/get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	**create_grid(int tiles)
{
	static int	gridSize;
	char		**tab;

	tab = NULL;
	if (gridSize == 0)
		gridSize = ft_sqrt(tiles * 4);
	else
		gridSize += 1;
	return (tab);
}

void	show_piece(char **tile)
{
	int y;

	y = 0;
	ft_putstr("Show piece:\n");
	while (y < 4)
	{
		ft_putstr(tile[y]);
		ft_putchar('\n');
		y++;
	}
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
	show_piece(tile);
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
	char	*buffer;
	char 	***test;

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
