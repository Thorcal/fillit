/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuisais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 11:50:40 by spuisais          #+#    #+#             */
/*   Updated: 2018/11/27 16:02:29 by spuisais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_countwords(char const *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (i == 0)
			if (str[i] != c)
				count++;
		if (str[i] == c)
			if (str[i + 1] != c)
				count++;
		i++;
	}
	return (count);
}

static int		ft_strlensplit(char const *str, int ind, char c)
{
	int i;
	int letters;
	int index;

	i = 0;
	letters = 0;
	index = 1;
	while (str[i] != '\0' && index != ind)
	{
		if (str[i] != c && str[i + 1] == c)
			index++;
		i++;
	}
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] != c)
			letters++;
		if (str[i] != c)
			if (str[i + 1] == c)
				return (letters);
		i++;
	}
	return (letters);
}

static char		**ft_fill_array(char **array, char const *str, char c)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		j = 0;
		if (str[i] == c)
			i++;
		else
		{
			while (str[i] && str[i] != c)
			{
				array[k][j] = str[i];
				j++;
				i++;
			}
			array[k][j] = '\0';
			k++;
		}
	}
	array[k] = 0;
	return (array);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**array;
	int		k;
	int		words;

	k = 0;
	if (!s)
		return (NULL);
	words = ft_countwords(s, c);
	if (!(array = (char**)malloc(sizeof(char*) * (words + 1))))
		return (NULL);
	while (k < words)
	{
		if (!(array[k] = (char*)malloc(sizeof(char) *
						(ft_strlensplit(s, k + 1, c) + 1))))
			return (NULL);
		k++;
	}
	ft_fill_array(array, s, c);
	return (array);
}
