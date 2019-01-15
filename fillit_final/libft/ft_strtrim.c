/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuisais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 11:02:08 by spuisais          #+#    #+#             */
/*   Updated: 2018/11/27 16:10:01 by spuisais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strtrim(char const *s)
{
	char	*str;
	size_t	i;
	size_t	k;
	size_t	j;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	k = ft_strlen(s);
	while (k > i && (s[k] == ' ' || s[k] == '\n' || s[k] == '\t'
			|| s[k] == '\0'))
		k--;
	k++;
	if (!(str = (char*)malloc(sizeof(char) * (k - i) + 1)))
		return (NULL);
	j = 0;
	while (i < k)
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}
