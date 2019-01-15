/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuisais <spuisais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:49:15 by spuisais          #+#    #+#             */
/*   Updated: 2018/11/19 13:57:52 by spuisais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char *str1;
	char *str2;

	if (!*needle)
		return ((char*)haystack);
	while (*haystack)
	{
		str1 = (char *)haystack;
		str2 = (char *)needle;
		while (*str2 && *haystack == *str2)
		{
			haystack++;
			str2++;
		}
		if (!*str2)
			return (str1);
		haystack = str1 + 1;
	}
	return (NULL);
}
