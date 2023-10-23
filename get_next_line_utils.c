/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:38:58 by mlezcano          #+#    #+#             */
/*   Updated: 2023/10/23 16:59:00 by mlezcano         ###   ########.fr       */
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

	if (NULL == list) //otra vez controlamos el NULL
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		while (list->buffer[i])
		{
			if (list->buffer[i] == '\n') // con esto controlamos si la cadena que estamos copiando ha llegado ya a salto de línea (es decir nueva línea)
			{
				str[j++] = '\n'; //en caso de ser así ponemos salto de línea en el siguiente lugar de la cadena copiada..
				str[j] = '\0'; //...ponemos carácter  nulo al final de la cadena..
				return ; // y retornamos.
			}
			str[j++] = list->buffer[i++]; //si no, simplemente copiamos la cadena
		}
		list = list->next; //con esto avanzamos al siguiente nodo después de haber copiado la cadena, hasta que entremos en el "while (list->buffer[i])"
	}
	str[j] = '\0'; //y si no hemos retornado antes, agregamos carácter nulo al final de lo copiado para poder operar con el resto de funciones
}

int	ft_newlinelength(t_list *list) //  cuenta la cantidadd de carácteres de la linea que vamos a leer
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
			if (list->buffer[i] == '\n') // '\n' sirve para comprobar si se trata de una nueva linea (recordamos que este carácter es igual a presionar enter para generar una nueva línea)
			{
				++length;
				return (length);
			}
			i++;
			length++;
		}
		list = list->next;
	}
	return (length);
}

void	dealloc(t_list **list, t_list *clean_node, char *buf)
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
