/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 14:16:39 by ljanuari          #+#    #+#             */
/*   Updated: 2026/08/26 16:27:20 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_realloc(char *s, int ps, int *size)
{
	char	*dup;

	if (size == 0)
		return (NULL);
	*size *= 2;
	dup = (char *) malloc((*size) * sizeof(char));
	if (!dup)
	{
		free(s);
		return (NULL);
	}
	dup[ps] = 0;
	while (ps--)
		dup[ps] = s[ps];
	free(s);
	return (dup);
}

t_list	*remember(t_list *heap, char **line, int fd)
{
	t_list	*pa;

	*line = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (*line == NULL)
		return (NULL);
	my_born(*line);
	pa = check(heap, fd);
	if (pa == NULL)
	{
		pa = (t_list *) malloc(sizeof(t_list));
		if (pa == NULL)
			return (NULL);
		pa->fd = fd;
		my_born(pa->buffer);
		pa->next = NULL;
		while (heap->next)
			heap = heap->next;
		heap->next = pa;
		pa->i = 0;
	}
	else
		pa->i = buffer_move(*line, pa->buffer, 0, BUFFER_SIZE + 1);
	pa->save = BUFFER_SIZE + 1;
	return (pa);
}

int	buffer_move(char *dest, char *buff, int start, int readt)
{
	int	i;
	int	x;
	int	aux;

	i = 0;
	if (!dest || !buff || readt <= 0)
		return (-1);
	aux = readt;
	while (readt-- && buff[i] && buff[i] != '\n')
		dest[start++] = buff[i++];
	dest[start] = 0;
	if (buff[i] == '\n')
	{
		i++;
		dest[start++] = '\n';
		dest[start] = 0;
		x = 0;
		while (i < aux && buff[i])
			buff[x++] = buff[i++];
		while (x < BUFFER_SIZE && buff[x])
			buff[x++] = 0;
		start = -500;
	}
	return (start);
}

void	ft_lstremove(t_list **heap, int fd)
{
	t_list	*ptr;
	t_list	*proximo;

	ptr = *heap;
	if (ptr == NULL)
		return ;
	if (ptr->fd == fd)
	{
		*heap = (*heap)->next;
		free(ptr);
		return ;
	}
	proximo = ptr->next;
	while (proximo && proximo->fd != fd)
	{
		ptr = proximo;
		proximo = proximo->next;
	}
	if (proximo)
		ptr->next = proximo->next;
	free(proximo);
}
