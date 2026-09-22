/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 10:12:31 by ljanuari          #+#    #+#             */
/*   Updated: 2026/08/28 10:17:44 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

typedef struct v_aux
{
	int			save;
	int			readt;
	char		*line;
	int			i;
}	t_helper;

void	buffer_move(char *buff, int start, int readt);
int		ft_strllcat(t_helper *pa, char *src);
char	*ft_realloc(char *s, t_helper *pa);
char	*get_next_line(int fd);
int		remember(char **line, char *buffer);
#endif
