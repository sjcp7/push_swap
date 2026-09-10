/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 11:32:15 by ljanuari          #+#    #+#             */
/*   Updated: 2026/08/03 17:18:59 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	number_leng(int n)
{
	long	x;
	int		re;

	x = n;
	re = 0;
	if (x == 0)
		return (1);
	if (x < 0)
	{
		x *= -1;
		re++;
	}
	while (x > 0)
	{
		x /= 10;
		re++;
	}
	return (re);
}

char	*ft_itoa(int n)
{
	int		size;
	long	x;
	char	*itoa;

	x = n;
	size = number_leng(n);
	itoa = (char *) malloc((size + 1) * sizeof(char));
	if (!itoa)
		return (NULL);
	if (n < 0)
	{
		x *= -1;
		itoa[0] = '-';
	}
	itoa[size] = '\0';
	if (x == 0)
		itoa[0] = '0';
	while (x && size--)
	{
		itoa[size] = (x % 10) + '0';
		x /= 10;
	}
	return (itoa);
}
