/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 12:20:21 by samupedr          #+#    #+#             */
/*   Updated: 2026/09/18 13:12:35 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	division1(t_stack *a, int *front_index, int *back_index, int k)
{
	int	rps;
	int	i;
	
	rps = a->size;
	i = a->head;
	*front_index = 0;
	while (rps--)
	{
		if (a->nums[i] < k)
			break ;
		*front_index += 1;
		if (i == 0)
			i = a->size;
		i = (i - 1) % a->size;
	}
	*back_index = 0;
	i = a->head;
	rps = a->size;
	while (rps--)
	{
		if (a->nums[i] < k)
			break ;
		*back_index += 1;
		i = (i + 1) % a->size;
	}
}	

static int	division2(t_stack *a, int *front_index, int *back_index, int *op)
{
	int	index;
	
	if (*back_index < *front_index)
	{
		*op = RA;
		index = *back_index;
		if (back_index > (a->size / 2))
		{
			*op = RRA;
			index = a->size - *back_index;
		}
	}
	else
	{
		*op = RRA;
		index = *front_index;
		if (*front_index > (a->size / 2))
		{
			*op = RA;
			index = a->size - *front_index;
		}
	}
	return (index);
}

static void	move_k(t_state *data, int k)
{
	int	front_index;
	int	back_index;
	int	index;
	int	op;
	
	division1(data->a, &front_index, &back_index, k);
	index = division2(data->a, &front_index, &back_index, &op);
	while (index--)
		operation(data, op);
}

void	chunk_sort(t_state *data)
{
	t_stack	*a;
	int	i;
	int	chunks;
	int	k;
	
	a = data->a;
	chunks = ps_sqrt(a->size);
	k = chunks;
	while (a->size)
	{
		i = chunks;
		while (i--)
		{
			move_k(data, k);
			find_posix(data, a->nums[a->head]);
			operation(data, op);
		}
		k += chunks;
	}	
}
