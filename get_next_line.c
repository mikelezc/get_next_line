/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:37:24 by mlezcano          #+#    #+#             */
/*   Updated: 2023/10/28 19:34:15 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_traincontainer(int fd, char *container)
{
	char	*buffer;
	int		size;

	size = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!gnl_strchr(container, '\n') && size > 0)
	{
		size = read(fd, buffer, BUFFER_SIZE);
		if (size == -1)
		{
			free(container);
			free(buffer);
			return (NULL);
		}
		buffer[size] = '\0';
		container = gnl_strjoin(container, buffer);
	}
	free(buffer);
	return (container);
}

char	*gnl_polish(char *container)
{
	char	*str;
	int		index;

	index = 0;
	if (!container[index])
		return (NULL);
	while (container[index] && container[index] != '\n')
		index++;
	str = malloc(sizeof(char) * (index + 2));
	index = 0;
	while (container[index] && container[index] != '\n')
	{
		str[index] = container[index];
		index++;
	}
	if (container[index] == '\n')
		str[index++] = '\n';
	str[index] = '\0';
	return (str);
}

char	*gnl_surplus(char *container)
{
	int		index;
	int		y;
	char	*str;

	index = 0;
	while (container[index] && container[index] != '\n')
		index++;
	if (!container[index])
	{
		free(container);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(container) - index + 1));
	if (!str)
		return (NULL);
	index++;
	y = 0;
	while (container[index])
	{
		str[y++] = container[index++];
	}
	str[y] = '\0';
	free(container);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*container;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	container = gnl_traincontainer(fd, container);
	if (!container)
		return (NULL);
	line = gnl_polish(container);
	container = gnl_surplus(container);
	return (line);
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
}*/

/*

Explicación rápida de la función write:
   
   ssize_t read(int fd, void *buf, size_t nbytes);

   - fd: descriptor de fichero de entrada, 
   - buf: puntero a un buffer de memoria y 
   - nbytes: número de bytes del buffer que queramos leer.
*/