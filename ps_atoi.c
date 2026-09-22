/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 09:07:16 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/22 12:44:09 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ps_atoi(const char *num, long *atoi)
{
	int		sign;

	sign = 1;
	*atoi = 0;
	if (*num == '+' || *num == '-')
	{
		if (*num == '-')
			sign = -1;
		num++;
	}
	if (!ft_isdigit(*num))
		return (0);
	while (ft_isdigit(*num))
	{
		*atoi = (*atoi * 10) + (*num - '0');
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
