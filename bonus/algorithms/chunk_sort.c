/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 12:20:21 by samupedr          #+#    #+#             */
/*   Updated: 2026/09/18 15:18:40 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

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

static void	move_k(t_state *data, int k)
{
	int			front_index;
	int			back_index;
	int			index;
	t_operation	op;

	find_k_distance(data->a, &front_index, &back_index, k);
	index = choose_way(data->a, front_index, back_index, &op);
	while (index--)
		operation(data, op);
}

void	chunk_sort(t_state *data)
{
	t_stack	*a;
	int		i;
	int		chunks;
	int		k;

	a = data->a;
	chunks = (ps_sqrt(a->size) * 3) / 2;
	k = chunks;
	while (a->size)
	{
		i = chunks;
		while (i--)
		{
			if (a->size == 0)
				break ;
			move_k(data, k);
			find_posix(data, a->nums[a->head]);
			operation(data, PB);
		}
		k += chunks;
	}
	find_max(data);
	while (data->b->size)
		operation(data, PA);
}
