/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuisais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 10:34:48 by spuisais          #+#    #+#             */
/*   Updated: 2018/11/19 11:08:35 by spuisais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char *dstcopy;
	char *srccopy;

	dstcopy = (char*)dst;
	srccopy = (char*)src;
	if (len == 0)
		return (dst);
	if (dstcopy < srccopy)
		while (len--)
			*dstcopy++ = *srccopy++;
	else
	{
		dstcopy += len;
		srccopy += len;
		while (len--)
			*--dstcopy = *--srccopy;
	}
	return (dst);
}
