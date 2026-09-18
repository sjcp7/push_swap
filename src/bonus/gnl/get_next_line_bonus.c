/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 10:17:39 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/18 15:08:05 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	t_helper	pa;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	pa.i = remember(&pa.line, buffer);
	if (pa.i < 0)
		return (pa.line);
	pa.save = BUFFER_SIZE + 1;
	pa.readt = 1;
	while (pa.readt > 0 && pa.i >= 0)
	{
		pa.readt = read(fd, buffer, BUFFER_SIZE);
		pa.i = ft_strllcat(&pa, buffer);
	}
	if (pa.line && (*pa.line) == '\0')
	{
		free(pa.line);
		return (NULL);
	}
	return (pa.line);
}
