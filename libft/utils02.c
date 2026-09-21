/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 14:39:41 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/18 12:57:00 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	arredondar(int num, int precision)
{
	int	pivot;

	pivot = 1;
	while (precision--)
		pivot *= 10;
	if (pivot == 1)
		return (0);
	while (num > pivot)
	{
		if ((num % 10) >= 5)
			num = (num / 10) + 1;
		else
			num = num / 10;
	}
	return (num);
}

int	my_printfloat(float n, t_format format)
{
	long	intpart;
	long	decimal_part;
	int		total;

	intpart = n;
	n -= intpart;
	n *= 100000;
	decimal_part = n;
	if (format.precision >= 0)
		decimal_part = arredondar(decimal_part, format.precision);
	ft_bzero(&format, sizeof(t_format));
	format.precision = -1;
	total = my_printnumber(intpart, format);
	total += my_printchar('.', format);
	total += my_printnumber(decimal_part, format);
	return (total);
}

static void	division_1(const char **format, t_format *flags, va_list *va)
{
	if (**format == '*')
	{
		flags->width = va_arg(*va, int);
		if (flags->width < 0)
		{
			flags->minus = 1;
			flags->width *= -1;
		}
		(*format)++;
	}
	else
	{
		while (ft_isdigit(**format))
		{
			flags->width = (flags->width * 10) + (**format - '0');
			++(*format);
		}
	}
}

static void	division_2(const char **format, t_format *flags, va_list *va)
{
	if (**format == '.')
	{
		(*format)++;
		if (**format == '*')
		{
			flags->precision = va_arg(*va, int);
			if (flags->precision < 0)
				flags->precision = -1;
			(*format)++;
		}
		else
		{
			while (ft_isdigit(**format))
			{
				flags->precision = (flags->precision * 10) + (**format - '0');
				(*format)++;
			}
		}
	}
	else
		flags->precision = -1;
}

void	true_parse(const char **format, t_format *flags, va_list *va)
{
	division_1(format, flags, va);
	division_2(format, flags, va);
}
