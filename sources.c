/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sources.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 14:12:38 by vrobin            #+#    #+#             */
/*   Updated: 2019/01/21 14:52:05 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

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
