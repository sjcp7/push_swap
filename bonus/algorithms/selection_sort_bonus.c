/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_sort_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 10:54:48 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/22 12:23:28 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap_bonus.h"

static int	find_min(t_stack *p)
{
	int	i;
	int	dif;
	int	index;
	int	reps;
	int	menor;

	if (p == NULL || p->size == 0)
		return (-1);
	i = p->head;
	menor = p->nums[i];
	index = 0;
	dif = 0;
	reps = p->size;
	while (--reps)
	{
		i = (i + 1) % p->size;
		dif++;
		if (p->nums[i] < menor)
		{
			menor = p->nums[i];
			index = dif;
		}
	}
	return (index);
}

void	reverse_op(int *index, int size, t_operation *op)
{
	t_operation	reverse;

	if (*op == RA || *op == RB)
	{
		reverse = RRB;
		if (*op == RA)
			reverse = RRA;
	}
	else
	{
		reverse = RB;
		if (*op == RRA)
			reverse = RA;
	}
	if (*index > (size / 2))
	{
		*index = size - *index;
		*op = reverse;
	}
}

void	selection_sort(t_state *data)
{
	int			index;
	t_operation	op;
	int			reps;
	t_stack		*a;
	t_stack		*b;

	if (data == NULL)
		return ;
	a = data->a;
	b = data->b;
	reps = a->size;
	while (--reps)
	{
		index = find_min(a);
		if (index == -1)
			return ;
		op = RA;
		reverse_op(&index, a->size, &op);
		while (index--)
			operation(data, op);
		operation(data, PB);
	}
	while (b->size)
		operation(data, PA);
}
