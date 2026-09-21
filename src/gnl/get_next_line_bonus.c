/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 10:17:39 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/21 16:54:56 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*check(t_list *heap, int fd)
{
	while (heap)
	{
		if (heap->fd == fd)
			return (heap);
		heap = heap->next;
	}
	return (NULL);
}

static int	div1(t_list **heap, int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!(*heap))
	{
		*heap = (t_list *) malloc(sizeof(t_list));
		if (*heap)
		{
			(*heap)->fd = fd;
			(*heap)->next = NULL;
			my_born((*heap)->buffer);
		}
		else
			return (0);
	}
	return (1);
}

void	my_born(char *buffer)
{
	int	i;

	i = BUFFER_SIZE + 1;
	while (i--)
		buffer[i] = 0;
}

static char	*div2(char *line)
{
	if (line && *line == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*heap;
	t_list			*pa;
	int				readt;
	char			*line;

	if (!div1(&heap, fd))
		return (NULL);
	pa = remember(heap, &line, fd);
	if (!pa)
		return (div2(line));
	readt = 1;
	while (readt > 0 && pa->i >= 0)
	{
		readt = read(fd, pa->buffer, BUFFER_SIZE);
		if (readt <= 0)
		{
			ft_lstremove(&heap, fd);
			return (div2(line));
		}
		pa->buffer[readt] = 0;
		if (readt >= pa->save - pa->i)
			line = ft_realloc(line, pa->i, &pa->save);
		pa->i = buffer_move(line, pa->buffer, pa->i, readt);
	}
	return (div2(line));
}
