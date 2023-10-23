/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:38:58 by mlezcano          #+#    #+#             */
/*   Updated: 2023/10/23 17:39:55 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_linedetector(t_list *list)
{
	int	i;

	if (NULL == list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->buffer[i] && i < BUFFER_SIZE)
		{
			if (list->buffer[i] == '\n')
				return (1);
			++i;
		}
		list = list->next;
	}
	return (0);
}

t_list	*ft_lastnode(t_list *list)
{
	if (NULL == list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	ft_copystr(t_list *list, char *str)
{
	int	i;
	int	j;

	if (NULL == list)
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		while (list->buffer[i])
		{
			if (list->buffer[i] == '\n')
			{
				str[j++] = '\n';
				str[j] = '\0';
				return ;
			}
			str[j++] = list->buffer[i++];
		}
		list = list->next;
	}
	str[j] = '\0';
}

int	ft_newlinelength(t_list *list)
{
	int	i;
	int	length;

	if (NULL == list)
		return (0);
	length = 0;
	while (list)
	{
		i = 0;
		while (list->buffer[i])
		{
			if (list->buffer[i] == '\n')
			{
				++length;
				return (length);
			}
			++i;
			++length;
		}
		list = list->next;
	}
	return (length);
}

void	ft_unalloc(t_list **list, t_list *clean_node, char *buf)
{
	t_list	*tmp;

	if (NULL == *list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->buffer);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (clean_node->buffer[0])
		*list = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}
