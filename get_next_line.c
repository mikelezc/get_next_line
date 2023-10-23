/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:37:24 by mlezcano          #+#    #+#             */
/*   Updated: 2023/10/23 14:26:07 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_attach(t_list **list, char *buf)
{
	

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

}

/*
Explicación rápida de la función write:
   
   ssize_t read(int fd, void *buf, size_t nbytes);

   - fd: descriptor de fichero de entrada, 
   - buf: puntero a un buffer de memoria y 
   - nbytes: número de bytes del buffer que queramos leer.
*/