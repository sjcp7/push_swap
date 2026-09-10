/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 09:07:16 by ljanuari          #+#    #+#             */
/*   Updated: 2026/08/03 09:08:06 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_white(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (c);
	if (c == '\r' || c == '\v' || c == '\f')
		return (c);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	signal;
	int	atoi;

	if (str == NULL)
		return (0);
	atoi = 0;
	signal = 1;
	while (is_white((char)*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			signal *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		atoi = (atoi * 10) + (*str++ - '0');
	return (atoi * signal);
}
