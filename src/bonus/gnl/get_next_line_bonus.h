/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 10:12:31 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/18 15:08:50 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

typedef struct v_aux
{
	int			save;
	int			readt;
	char		*line;
	int			i;
}	t_helper;

void	buffer_move(char *buff, int start, int readt);
int		gnl_strllcat(t_helper *pa, char *src);
char	*gnl_realloc(char *s, t_helper *pa);
char	*get_next_line(int fd);
int		remember(char **line, char *buffer);
#endif
