/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 12:20:21 by samupedr          #+#    #+#             */
/*   Updated: 2026/09/22 12:44:09 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	find_k_distance(t_stack *a, int *front, int *back, int k)
{
	int	rps;
	int	i;

	rps = a->size;
	i = a->head;
	*front = 0;
	while (rps--)
	{
		if (a->nums[i] < k)
			break ;
		*front += 1;
		i = (i + 1) % a->size;
	}
	*back = 0;
	i = a->head;
	rps = a->size;
	while (rps--)
	{
		if (a->nums[i] < k)
			break ;
		*back += 1;
		if (i == 0)
			i = a->size;
		i = (i - 1) % a->size;
	}
}

static int	choose_way(t_stack *a, int front, int back, t_operation *op)
{
	int	index;

	if (back < front)
	{
		*op = RRA;
		index = back;
		reverse_op(&index, a->size, op);
	}
	else
	{
		*op = RA;
		index = front;
		reverse_op(&index, a->size, op);
	}
	return (index);
}

static int	move_k(t_state *data, int k)
{
	int			front_index;
	int			back_index;
	int			index;
	t_operation	op;

	find_k_distance(data->a, &front_index, &back_index, k);
	index = choose_way(data->a, front_index, back_index, &op);
	while (index--)
		if (operation(data, op) == 0)
			return (0);
	return (1);
}

static int	push_chunks(t_state *data, int chunks)
{
	int		k;
	int		i;
	t_stack	*a;

	k = chunks;
	a = data->a;
	while (a->size)
	{
		i = chunks;
		while (i--)
		{
			if (a->size == 0)
				break ;
			if (!move_k(data, k))
				return (0);
			if (!find_posix(data, a->nums[a->head]))
				return (0);
			if (operation(data, PB) == 0)
				return (0);
		}
		k += chunks;
	}
	return (1);
}

void	chunk_sort(t_state *data)
{
	int	chunks;

	chunks = (ps_sqrt(data->a->size) * 3) / 2;
	if (push_chunks(data, chunks) == 0)
		return ;
	if (!find_max(data))
		return ;
	while (data->b->size)
		if (operation(data, PA) == 0)
			return ;
}
