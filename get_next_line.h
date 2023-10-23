/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:38:25 by mlezcano          #+#    #+#             */
/*   Updated: 2023/10/23 13:00:17 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_list
{
	char			*buffer;
	struct s_list	*next;
}	t_list;


char	*get_next_line(int fd);

#endif
