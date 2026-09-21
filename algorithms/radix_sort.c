/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 12:24:32 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/18 15:16:32 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	count_bits(int maior)
{
	int	i;

	i = 0;
	while (maior)
	{
		i++;
		maior /= 2;
	}
	return (i);
}

void	radix_sort(t_state *data)
{
	int	nbr_bits;
	int	x;
	int	i;
	int	bit;

	if (!data->a || !data->b)
		return ;
	nbr_bits = count_bits(data->a->size);
	i = 0;
	while (i < nbr_bits)
	{
		bit = 1 << i;
		x = data->a->size;
		while (x--)
		{
			if (data->a->nums[data->a->head] & bit)
				operation(data, RA);
			else
				operation(data, PB);
		}
		while (data->b->size)
			operation(data, PA);
		i++;
	}
}
