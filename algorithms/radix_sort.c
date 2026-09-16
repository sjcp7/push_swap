/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 12:24:32 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/16 12:24:59 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	normalizer(t_stack *a)
{
	int	*radix_cpy;
	int	x;
	int	i;
	int	j;
		
	radix_cpy = (int *)malloc(sizeof(int) * a->size);
	if (radix_cpy == NULL)
		return (0);
	ft_memmove(radix_cpy, a->nums, (a->size * sizeof(int)));
	ps_merge_sort(radix_cpy, 0, a->size - 1);
	x = a->size;
	j = 0;
	while (j < x)
	{
		i = -1;
		while (++i < x)
			if (a->nums[i] == radix_cpy[j])
				break ;
		a->nums[i] = j++;
	}
	free(radix_cpy);
	return (1);			
}

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
