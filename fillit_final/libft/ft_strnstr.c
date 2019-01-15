/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuisais <spuisais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 14:16:11 by spuisais          #+#    #+#             */
/*   Updated: 2018/11/27 15:25:49 by spuisais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	if (!*needle && !*haystack)
		return ((char*)haystack);
	while (haystack[j])
	{
		i = 0;
		while (needle[i] && haystack[j + i] == needle[i] && (i + j) < len)
			i++;
		if (needle[i] == '\0')
			return ((char*)&haystack[j]);
		j++;
	}
	return (NULL);
}
