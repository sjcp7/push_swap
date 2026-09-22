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

#include "../includes/push_swap.h"

int	ps_atoi(const char *num, long *atoi)
{
	int		sign;
	int		c;

	sign = 1;
	*atoi = 0;
	if (*num == '+' || *num == '-')
	{
		if (*num == '-')
			sign = -1;
		num++;
	}
	while ((*num >= '0' && *num <= '9'))
	{
		c = (*num - '0');
		*atoi = (*atoi * 10) + c;
		if (sign == 1 && *atoi > 2147483647)
			return (0);
		if (sign == -1 && (*atoi * -1) < -2147483648)
			return (0);
		num++;
	}
	if (*num)
		return (0);
	*atoi *= sign;
	return (1);
}
