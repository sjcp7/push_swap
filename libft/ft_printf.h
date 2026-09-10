/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 09:51:00 by ljanuari          #+#    #+#             */
/*   Updated: 2026/08/13 11:54:41 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

typedef struct s_format
{
	int		zero;
	int		plus;
	int		minus;
	int		space;
	int		hash;
	int		width;
	int		precision;
	char	identifi;
}	t_format;

int	my_strlimprint(char *s, int lim);
int	my_printchar(char c, t_format format);
int	my_printstr(char *s, t_format format);
int	my_printnumber(int n, t_format format);
int	my_printnumber_u(unsigned int n, t_format format);
int	my_printadress(void *adr, t_format format);
int	my_printhex(unsigned int n, t_format format);
int	my_printfloat(float n);
int	ft_printf(const char *s, ...);
#endif
