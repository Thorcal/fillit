/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuisais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 17:12:53 by spuisais          #+#    #+#             */
/*   Updated: 2018/12/03 17:33:24 by spuisais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinf(char **s1, char **s2, int k)
{
	int		i;
	char	*str;

	if (*s1 && *s2)
	{
		i = ft_strlen(*s1) + ft_strlen(*s2);
		if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
			return (NULL);
		ft_strcpy(str, *s1);
		ft_strcat(str, *s2);
		if (k == 1)
			free(*s1);
		else if (k == 2)
			free(*s2);
		else if (k == 3)
		{
			free(*s1);
			free(*s2);
		}
		return (str);
	}
	return (NULL);
}
