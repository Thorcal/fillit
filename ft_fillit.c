/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fillit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuisais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 11:17:22 by spuisais          #+#    #+#             */
/*   Updated: 2019/01/14 15:50:37 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "libft/get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

/* Marche avec + de 5 tuiles mais rentre dans la stack
 * pb -> buff_size
*/ 

void	aff_tetro(char **tab, int size) // norme
{
	int i;

	i = 0;
	while (i < size)
		ft_putendl(tab[i++]);
}

void	clear(char **tab, int size, int current) // norme
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

void	place_tile(char **tab, char **tile, int y, int x) // norme
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

int		check_spot(char **tab, char **tile, int y, int x, int size) // 5 parametres
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

void	aff_test(char ***test, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		ft_putendl(*test[i]);
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
		aff_tetro(tab, size);
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

char	**create_grid(int size) // 29 lignes
{
	char		**tab;
	char		**tmp;
	int			i;
	int			j;

	j = 0;
	tmp = NULL;
	i = size;
	if (!(tab = (char**)malloc(sizeof(char*) * size)))
		return (NULL);
	i = 0;
	tab[size] = NULL;
	while (i < size)
		if (!(tab[i++] = ft_strnew(size)))
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

char	**move_upper_left(char **tile) // 37 lignes
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

int		count_connections(char **tile, int y, int x) // norme
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

int		get_connections(char **tile) // norme
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

char	**fill_piece(char *buffer) // 32 lignes + 2 mallocs a free
{
	static char	character = '@';
	static int	i = 0;
	int			x;
	int			y;
	char		**piece_tab;

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

int		is_valid(char *buffer, int buflen) // norme
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
			if (buffer[i++] == '#')
				blocs++;
			len++;
		}
		if ((lnum % 5 == 0 && len != 0) || (lnum % 5 == 0 && blocs != 4)
				|| (lnum % 5 != 0 && len != 4))
			return (-1);
		if (lnum++ % 5 == 0)
			blocs = 0;
		i++;
	}
	return ((lnum + 1) / 5);
}

int		print_tile(fd)
{
	int		i;
	int		j;
	int		tiles;
	int		size;
	char	*buffer; //free
	char 	***test; //free
	char	**grid;

	j = 0;
	if (!(buffer = ft_strnew(BUFF_SIZE + 1)))
		return (-1);
	i = read(fd, buffer, BUFF_SIZE);
	if ((tiles = is_valid(buffer, i)) == -1)
		return (-1);
	if (!(test = (char***)malloc(sizeof(char**) * tiles + 1)))
		return (-1);
	test[tiles] = NULL;
	while (j < tiles)
	{
		if (!(test[j] = (char**)malloc(sizeof(char*) * 4)))
			return (-1);
		test[j][4] = NULL;
		test[j] = fill_piece(buffer);
		if (get_connections(test[j]) != 1)
			return (-1);
		j++;
	}
	size = high_sqrt(tiles * 4);
	grid = create_grid(size);
	while (place_tiles(tiles, grid, size, test, 0) != 1)
	{
		size += 1;
		ft_memdel((void*)grid);
		grid = create_grid(size);
	}
	free(test);
	free(buffer);
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
			ft_putstr("Erreur\n");
	}
	else
		ft_putstr("usage: ./fillit source_file");
}
