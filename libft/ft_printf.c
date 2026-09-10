/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 12:16:29 by ljanuari          #+#    #+#             */
/*   Updated: 2026/08/21 10:41:51 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	true_parse(const char **format, t_format *flags, va_list *va);

void	print_reverse(char const *s)
{
	int	i;

	i = ft_strlen(s);
	while (i--)
		write(1, &s[i], 1);
}

void	upper_hex(char *hex, int c)
{
	if (c == 'x')
		return ;
	while (*hex)
	{
		*hex = (char)ft_toupper((int)*hex);
		(hex)++;
	}
}

static int	parse_flags(const char *format, t_format *flags, va_list *va)
{
	while (ft_strchr("-0+ #", *++format) != NULL)
	{
		if (*format == '-')
			flags->minus = 1;
		else if (*format == '0')
			flags->zero = 1;
		else if (*format == '+')
			flags->plus = 1;
		else if (*format == ' ')
			flags->space = 1;
		else if (*format == '#')
			flags->hash = 2;
	}
	true_parse(&format, flags, va);
	if (ft_strchr("cspdfiuxX%", *format))
		flags->identifi = *format;
	return (flags->identifi != 0);
}

static int	putva(t_format *flags, va_list *ptr)
{
	if (flags->identifi == 'c')
		return (my_printchar((char)va_arg(*ptr, int), *flags));
	else if (flags->identifi == 's')
		return (my_printstr(va_arg(*ptr, char *), *flags));
	else if (flags->identifi == 'p')
		return (my_printadress(va_arg(*ptr, void *), *flags));
	else if (flags->identifi == 'd' || flags->identifi == 'i')
		return (my_printnumber(va_arg(*ptr, int), *flags));
	else if (flags->identifi == 'u')
		return (my_printnumber_u(va_arg(*ptr, unsigned int), *flags));
	else if (flags->identifi == 'x' || flags->identifi == 'X')
		return (my_printhex(va_arg(*ptr, unsigned int), *flags));
	else if (flags->identifi == '%')
		return (write(1, "%", 1));
	else if (flags->identifi == 'f')
		return (my_printfloat((float)va_arg(*ptr, double)));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int			count;
	va_list		ptr;
	t_format	flags;

	va_start(ptr, format);
	count = 0;
	if (!format)
		return (-1);
	while (*format)
	{
		if (*format != '%')
			count += my_strlimprint((char *)format++, 1);
		else
		{
			ft_bzero(&flags, sizeof(t_format));
			if (!parse_flags(format++, &flags, &ptr))
				count += write(1, format - 1, 1);
			else
				count += putva(&flags, &ptr);
			while (flags.identifi != 0 && !ft_strchr("cspdfiuxX%", *format++))
				;
		}
	}
	va_end(ptr);
	return (count);
}
