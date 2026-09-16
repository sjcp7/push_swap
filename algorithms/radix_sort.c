/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 12:24:32 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/16 12:51:08 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	radix_sort(t_state *data)
{
	int	c;
	int	x;
	int	i;
	int	k;

	if (!data->a || !data->b)
		return ;
	c = data->a->size;
	if (!normalizer(data->a))
		return ;
	i = 0;
	while (c)
	{
		i++;
		c /= 2;
	}
	c = i;
	i = 0;
	while (i < c)
	{
		k = 1 << i;
		x = data->a->size;
		while (x--)
			if (data->a->nums[data->a->head] & k)
				operation(data, RA);
			else
				operation(data, PB);
		while (data->b->size)
			operation(data, PA);
		i++;
	}
}
