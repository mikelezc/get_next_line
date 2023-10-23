/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:37:24 by mlezcano          #+#    #+#             */
/*   Updated: 2023/10/23 17:15:19 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_cleanlist(t_list **list) //función usada para limpiar los carácteres no usados de la última copia de buffer después del salto de línea
{
	t_list	*last;
	t_list	*clean;
	int		i;
	int		j;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean = malloc(sizeof(t_list));
	if (NULL == buf || NULL == clean)
		return ;
	last = ft_lastnode(*list);
	i = 0;
	j = 0;
	while (last->buffer[i] && last->buffer[i] != '\n') //mientras "last->buffer[i]" no sea igual a cero, o haya un salto de línea.
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

	if (NULL == list) //controlamos que la lista no de vacía, es redundante pero por seguridad es mejor controlar cada función por separado.
		return (NULL);
	length = ft_newlinelength(list);
	next = malloc(length + 1);
	if (NULL == next)
		return (NULL);
	ft_copystr(list, next);
	return (next);

}

void	ft_attach(t_list **list, char *buf) // función para unir cachos de texto
{
	t_list	*new;
	t_list	*previous;

	previous = ft_lastnode(*list);
	new = malloc(sizeof(t_list));
	if (NULL == new) // control de malloc
		return ;
	if (NULL == previous) //si no hay nada almacenado de antes (por ejemplo porque es la primera vez que leemos)
		*list = new;
	else
		previous->next = new;
	new->buffer = buf;
	new->next = NULL;
}

void	ft_nodetext(t_list **list, int fd) //genera cachos de texto leidos del fd y los almacena en structs
{
	int		char_count;
	char	*buffer;
	
	while (!ft_linedetector(*list)) // en caso de no encontrar una linea
	{
		buffer = malloc(BUFFER_SIZE + 1); // donde vamos a almacenar el string
		if (NULL == buffer) // control de malloc
			return;
		char_count = read(fd, buffer, BUFFER_SIZE); //read nos va a devolver la cantidad de caracteres leidos
		if (!char_count) //control que nos dice que si la cantidad carácteres es cero, es que el archivo ha llegado a su fin o está vacío, por eso libera el buffer y nos retorna la función
		{
			free(buffer);
			return;
		}
		buffer[char_count] = '\0'; // coloca el carácter nulo al final de la línea almacenada en el buffer
		ft_attach(list, buffer);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL; //creamos un nodo que apunte a nulo
	char			*next; // string que hará las veces de buffer

// este es nuestro filtro en caso de que fd sea negativo(siempre tiene que ser positivo), 
//o que el tamaño de buffer sea inferior a 0, o que la función read de error (-1),
// aquí la estamos usando simplemente para comprobar si el archivo que vamos a leer, pede ser abierto (si tiene permisos, etc).
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next, 0) < 0) 
		return (NULL);
	ft_nodetext(&list, fd); //función para crear un nodo de texto leido de un fd

	if (list == NULL)
		return (NULL);
	next = ft_obtain_line(list);
	ft_cleanlist(&list);
	return (next);

}

/*
Explicación rápida de la función write:
   
   ssize_t read(int fd, void *buf, size_t nbytes);

   - fd: descriptor de fichero de entrada, 
   - buf: puntero a un buffer de memoria y 
   - nbytes: número de bytes del buffer que queramos leer.
*/