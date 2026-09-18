/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 14:16:39 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/18 15:09:32 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*gnl_realloc(char *s, t_helper *pa)
{
	char	*dup;
	int		ps;

	if (pa->readt < pa->save - pa->i)
		return (s);
	if (pa->save == 1)
		return (NULL);
	pa->save *= 2;
	dup = (char *) malloc((pa->save) * sizeof(char));
	if (!dup)
		return (NULL);
	ps = pa->i;
	dup[ps] = 0;
	while (ps--)
		dup[ps] = s[ps];
	free(s);
	return (dup);
}

int	remember(char **line, char *buffer)
{
	int	len;
	int	i;

	i = 0;
	*line = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (*line == NULL)
		return (-1);
	len = 0;
	while (buffer[i] && buffer[i] != '\n')
		(*line)[len++] = buffer[i++];
	(*line)[len] = '\0';
	if (buffer[i] == '\n')
	{
		(*line)[len++] = '\n';
		(*line)[len] = '\0';
		i++;
		len = -500;
	}
	buffer_move(buffer, i, BUFFER_SIZE);
	return (len);
}

void	buffer_move(char *buff, int start, int readt)
{
	int	i;

	i = 0;
	while (start <= readt && buff[start])
		buff[i++] = buff[start++];
	while (buff[i])
		buff[i++] = 0;
}

int	gnl_strllcat(t_helper *pa, char *src)
{
	int	x;
	int	aux;

	if (!(pa->line) || !src || pa->readt < 0)
		return (-1);
	aux = pa->readt;
	pa->line = ft_realloc(pa->line, pa);
	if (!pa->line)
		return (-1);
	x = 0;
	while (aux-- && src[x] && src[x] != '\n')
		(pa->line)[(pa->i)++] = src[x++];
	(pa->line)[pa->i] = '\0';
	if (src[x] == '\n')
	{
		(pa->line)[pa->i++] = '\n';
		(pa->line)[pa->i] = '\0';
		pa->i = -500;
		++x;
	}
	buffer_move(src, x, pa->readt);
	return (pa->i);
}
