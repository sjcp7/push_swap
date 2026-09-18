/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:04:03 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/18 12:57:00 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

int		nbr_leng(int nbr);
int		fill(char c, int size);
void	upper_hex(char *hex, int c);
int		print_sign(int n, t_format format);
int		get_len(int n, t_format format, int digits);
int		aux_pads(t_format format, int len);
int		pads(int width, int len);
void	print_reverse(char const *s);

int	my_printchar(char c, t_format format)
{
	int	count;

	count = 0;
	if (format.width)
	{
		if (format.minus)
		{
			count += write(1, &c, 1);
			count += fill(' ', --format.width);
			return (count);
		}
		count += fill(' ', --format.width);
		count += write(1, &c, 1);
		return (count);
	}
	return (write(1, &c, 1));
}

int	my_printstr(char *s, t_format format)
{
	int	count;
	int	length;

	count = 0;
	length = format.width;
	if (!s)
		s = "(null)";
	if (format.precision >= 0 && format.precision < (int)ft_strlen(s))
		length -= format.precision;
	else
		length -= ft_strlen(s);
	if (length < 0)
		length = 0;
	if (format.minus == 0 && format.width)
		count += fill(' ', length);
	if (format.precision >= 0)
		count += my_strlimprint(s, format.precision);
	else
	{
		ft_putstr_fd(s, 1);
		count += ft_strlen(s);
	}
	if (format.minus == 1 && format.width)
		count += fill(' ', length);
	return (count);
}

int	my_printnumber(int n, t_format format)
{
	int	digits;
	int	leng;
	int	pad;
	int	count;

	digits = nbr_leng(n) - (n < 0);
	leng = get_len(n, format, digits);
	pad = pads(format.width, leng);
	count = 0;
	if (!format.minus && !format.zero && format.precision <= 0 && format.width)
		count += fill(' ', pad + (n == 0 && format.precision == 0));
	if (!format.minus && format.precision > 0 && format.width)
		count += fill(' ', pad);
	count += print_sign(n, format);
	if (format.zero && format.precision <= 0 && format.width)
		count += fill('0', pad);
	if (format.precision > digits)
		count += fill('0', format.precision - digits);
	if (n != 0 || format.precision != 0)
		ft_putnbr_fd(n, 1);
	count += nbr_leng(n);
	if (format.minus && (!format.zero || format.precision < 0) && format.width)
		count += fill(' ', pad);
	return (count);
}

int	my_printadress(void *adr, t_format format)
{
	unsigned long	rda;
	char			*hex;
	char			adress[18];
	int				i;
	int				count;

	hex = "0123456789abcdef";
	rda = (unsigned long)adr;
	count = 0;
	if (!adr)
		return (my_strlimprint("(nil)", 5));
	while (rda)
	{
		adress[count++] = hex[rda % 16];
		rda /= 16;
	}
	count += my_strlimprint("0x", 2);
	i = count - 2;
	if (format.minus == 0 && format.width)
		count += fill(' ', pads(format.width, count));
	while (i)
		write(1, &adress[--i], 1);
	if (format.minus == 1 && format.width)
		count += fill(' ', pads(format.width, count));
	return (count);
}

int	my_printhex(unsigned int n, t_format format)
{
	char	*hex;
	char	p[16];
	int		count;

	hex = "0123456789abcdef";
	count = 0;
	if (!n)
		p[count++] = '0';
	while (n && count < 8)
	{
		p[count++] = hex[n % 16];
		n /= 16;
	}
	p[count] = 0;
	upper_hex(p, format.identifi);
	n += aux_pads(format, count + format.hash);
	if (p[count -1] != '0' && format.hash && format.identifi == 'x')
		count += my_strlimprint("0x", 2);
	else if (p[count - 1] != '0' && format.hash && format.identifi == 'X')
		count += my_strlimprint("0X", 2);
	print_reverse(p);
	if (format.minus && (!format.zero || format.precision < 0) && format.width)
		count += fill(' ', pads(format.width, count));
	return (count + n);
}
