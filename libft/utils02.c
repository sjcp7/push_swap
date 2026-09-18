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

int	my_printfloat(float n)
{
	long	intpart;
	t_format format;
	long	decimal_part;
	
	ft_bzero(&format, sizeof(t_format));
	format.precision = -1;
	intpart = n;
	n -= intpart;
	n *= 100000;
	decimal_part = n;
	return (my_printnumber(intpart, format) + my_printchar('.', format) + my_printnumber(decimal_part, format));
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
