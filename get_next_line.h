/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:38:25 by mlezcano          #+#    #+#             */
/*   Updated: 2023/10/23 17:39:37 by mlezcano         ###   ########.fr       */
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
# include <fcntl.h>

typedef struct s_list
{
	char			*buffer;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
int		ft_linedetector(t_list *list);
void	ft_attach(t_list **list, char *buf);
void	ft_nodetext(t_list **list, int fd);
t_list	*ft_lastnode(t_list *list);
char	*ft_obtain_line(t_list *list);
int		ft_newlinelength(t_list *list);
void	ft_copystr(t_list *list, char *str);
void	ft_cleanlist(t_list **list);
void	ft_unalloc(t_list **list, t_list *clean_node, char *buf);

#endif
