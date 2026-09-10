/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 14:02:41 by ljanuari          #+#    #+#             */
/*   Updated: 2026/08/14 14:36:12 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	fill(char c, int size);
int	pads(int width, int len);

int	get_len(int n, t_format format, int digits)
{
	if (format.precision > digits)
		digits = format.precision;
	return (digits + (n < 0 || format.plus || format.space));
}

int	print_sign(int n, t_format format)
{
	if (n < 0)
	{
		write(1, "-", 1);
		return (0);
	}
	if (format.plus)
		return (write(1, "+", 1));
	if (format.space)
		return (write(1, " ", 1));
	return (0);
}

static int	nbr_leng_u(unsigned int nbr)
{
	int	x;

	x = 0;
	if (nbr == 0)
		return (1);
	while (nbr)
	{
		nbr /= 10;
		x++;
	}
	return (x);
}

static int	ft_putnbr_u_fd(unsigned int n, int fd)
{
	char	c;
	int		count;

	count = 0;
	if (n >= 10)
		count += ft_putnbr_u_fd(n / 10, fd);
	c = (n % 10) + '0';
	return (count + write(fd, &c, 1));
}

int	my_printnumber_u(unsigned int n, t_format format)
{
	int	count;
	int	zeros;
	int	sp;

	count = nbr_leng_u(n);
	if (n == 0 && format.precision == 0)
		count = 0;
	zeros = pads(format.precision, count);
	sp = pads(format.width, (count + zeros));
	count = 0;
	if (!format.minus)
	{
		if (format.zero && format.precision < 0)
		{
			zeros = sp;
			sp = 0;
		}
		count += fill(' ', sp);
		sp = 0;
	}
	count += fill('0', zeros);
	if (!(n == 0 && format.precision == 0))
		count += ft_putnbr_u_fd(n, 1);
	count += fill(' ', sp);
	return (count);
}
