/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:38:25 by mlezcano          #+#    #+#             */
/*   Updated: 2023/10/28 16:59:51 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*gnl_strchr(const char *word, char chr);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char const *word);
char	*get_next_line(int fd);
char	*ft_fillcontainer(int fd, char *container);
char	*ft_refillcontainer(char *container);
char	*ft_get_line(char *container);

#endif
