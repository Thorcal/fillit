/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuisais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 11:20:53 by spuisais          #+#    #+#             */
/*   Updated: 2018/12/04 14:27:54 by spuisais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*ft_half(char **str)
{
	int i;

	i = 0;
	while ((*str)[i] != '\n' && (*str)[i] != '\0')
		i++;
	if ((*str)[i] == '\0')
		return (NULL);
	(*str)[i] = '\0';
	return (ft_strdup((*str) + i + 1));
}

static	t_file	*ft_get_file_data(int fd, t_file **head)
{
	t_file	*temp;
	t_file	*previous;

	previous = NULL;
	temp = *head;
	while (temp != NULL)
	{
		if (temp->fd == fd)
			return (temp);
		previous = temp;
		temp = temp->next;
	}
	if (!(temp = (t_file*)malloc(sizeof(t_file))))
		return (NULL);
	temp->fd = fd;
	temp->reste = NULL;
	temp->next = NULL;
	if (previous != NULL)
		previous->next = temp;
	else
		*head = temp;
	return (temp);
}

int				get_next_line(int fd, char **line)
{
	static t_file	*head;
	t_file			*filedata;
	char			*str;
	char			*buffer;
	int				i;

	filedata = ft_get_file_data(fd, &head);
	str = ft_strnew(0);
	if (filedata->reste)
		str = ft_strjoinf(&str, &filedata->reste, 3);
	if (!(buffer = ft_strnew(BUFF_SIZE)) || fd < 0)
		return (-1);
	while (!(ft_strchr(str, '\n')) && (i = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		str = ft_strjoinf(&str, &buffer, 1);
		ft_bzero(buffer, BUFF_SIZE);
	}
	free(buffer);
	if (i < 0)
		return (-1);
	filedata->reste = ft_half(&str);
	*line = ft_strdup(str);
	free(str);
	i = (i > 0 || ft_strlen(*line) > 0) ? 1 : 0;
	return (i);
}
