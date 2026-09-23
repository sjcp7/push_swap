/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 12:24:32 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/22 12:44:09 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

static int	radix_pass(t_state *data, int bit)
{
	int	valid;
	int	x;

	x = data->a->size;
	while (x--)
	{
		if (data->a->nums[data->a->head] & bit)
			valid = operation(data, RA);
		else
			valid = operation(data, PB);
		if (valid == 0)
			return (0);
	}
	while (data->b->size)
		if (operation(data, PA) == 0)
			return (0);
	return (1);
}

int	radix_sort(t_state *data)
{
	int	nbr_bits;
	int	i;

	if (!data->a || !data->b)
		return (0);
	nbr_bits = count_bits(data->a->size - 1);
	i = 0;
	while (i < nbr_bits)
		if (!radix_pass(data, 1 << i++))
			return (0);
	return (1);
}
