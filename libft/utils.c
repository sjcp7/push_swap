/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 09:10:00 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/18 12:58:23 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nbr_leng(int nbr)
{
	int	x;

	x = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		x++;
		nbr *= -1;
	}
	while (nbr)
	{
		nbr /= 10;
		x++;
	}
	return (x);
}

int	my_strlimprint(char *s, int lim)
{
	int	count;

	count = 0;
	if (!s)
		return (count);
	while (*s && lim)
	{
		count += write(1, s++, 1);
		lim--;
	}
	return (count);
}

int	fill(char c, int size)
{
	int	count;

	count = 0;
	if (size < 0)
		size *= -1;
	while (size--)
		count += write(1, &c, 1);
	return (count);
}

int	pads(int width, int len)
{
	if (width - len < 0)
		return (0);
	else
		return (width - len);
}

int	aux_pads(t_format format, int len)
{
	int	count;

	count = 0;
	if (!format.minus && !format.zero && format.precision < 0 && format.width)
		count += fill(' ', pads(format.width, len));
	if (format.precision > 0 && format.width)
		count += fill(' ', pads(format.width, len));
	if (format.precision >= len)
		count += fill('0', format.precision - len);
	else if (format.zero && format.precision < 0 && format.width)
		count += fill('0', pads(format.width, len));
	return (count);
}
