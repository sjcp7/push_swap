/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 16:58:15 by ljanuari          #+#    #+#             */
/*   Updated: 2026/08/14 11:04:16 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	long	number;

	number = n;
	if (fd < 0)
		return ;
	if (n < 0)
		number *= -1;
	c = (number % 10) + '0';
	number /= 10;
	if (number > 0)
		ft_putnbr_fd(number, fd);
	write(fd, &c, 1);
}
