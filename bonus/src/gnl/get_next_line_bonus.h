/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 10:12:31 by ljanuari          #+#    #+#             */
/*   Updated: 2026/08/26 12:46:47 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

typedef struct s_list
{
	struct s_list	*next;
	int				save;
	int				i;
	int				fd;
	char			buffer[BUFFER_SIZE + 1];
}	t_list;

int		buffer_move(char *line, char *buff, int start, int n);
t_list	*check(t_list *heap, int fd);
void	my_born(char *buffer);
char	*ft_realloc(char *s, int ps, int *size);
char	*get_next_line(int fd);
void	ft_lstremove(t_list **heap, int fd);
t_list	*remember(t_list *heap, char **line, int fd);
#endif
