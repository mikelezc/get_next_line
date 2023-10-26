/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:37:24 by mlezcano          #+#    #+#             */
/*   Updated: 2023/10/26 14:50:41 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_cleanlist(t_list **list)
{
	t_list	*last;
	t_list	*clean;
	int		i;
	int		j;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean = malloc(sizeof(t_list));
	if (NULL == buf || NULL == clean)
	{
		free(buf);
		free(clean);
		return ;
	}	
	last = ft_lastnode(*list);
	i = 0;
	j = 0;
	while (last->buffer[i] && last->buffer[i] != '\n')
		++i;
	while (last->buffer[i] && last->buffer[++i])
		buf[j++] = last->buffer[i];
	buf[j] = '\0';
	clean->buffer = buf;
	clean->next = NULL;
	ft_unalloc(list, clean, buf);
}

char	*ft_obtain_line(t_list *list)
{
	int		length;
	char	*next;

	if (NULL == list)
		return (NULL);
	length = ft_newlinelength(list);
	next = malloc(length + 1);
	if (NULL == next)
		return (NULL);
	ft_copystr(list, next);
	return (next);
}

void	ft_attach(t_list **list, char *buf)
{
	t_list	*new;
	t_list	*previous;

	previous = ft_lastnode(*list);
	new = malloc(sizeof(t_list));
	if (NULL == new)
		return ;
	if (NULL == previous)
		*list = new;
	else
		previous->next = new;
	new->buffer = buf;
	new->next = NULL;
}

void	ft_nodetext(t_list **list, int fd)
{
	int		char_count;
	char	*buffer;

	while (!ft_linedetector(*list))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (NULL == buffer)
			return ;
		char_count = read(fd, buffer, BUFFER_SIZE);
		if (!char_count)
		{
			free(buffer);
			return ;
		}
		if (char_count == -1)
		{
			free((*list)->buffer);
			free(*list);
			return ;
		}
		buffer[char_count] = '\0';
		ft_attach(list, buffer);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next, 0) < 0)
	{
		if (list)
		{
			ft_cleanlist(&list);
			list = NULL;
		}
		return (NULL);
	}
	ft_nodetext(&list, fd);
	if (list == NULL)
		return (NULL);
	next = ft_obtain_line(list);
	ft_cleanlist(&list);
	return (next);
}
/*
int	main(void)
{
	int		fd;                             
	char	*line;                         
	int		lines;                          

	lines = 1;                              
	fd = open("test.txt", O_RDONLY);       

	while ((line = get_next_line(fd)))      
		printf("%d->%s\n", lines++, line);
	close(fd);
	return (0);
}
*/
/*
Explicación rápida de la función write:
   
   ssize_t read(int fd, void *buf, size_t nbytes);

   - fd: descriptor de fichero de entrada, 
   - buf: puntero a un buffer de memoria y 
   - nbytes: número de bytes del buffer que queramos leer.
*/