/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 10:54:48 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/14 10:55:15 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

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
		if (i == 0)
			i = p->size;
		i = (i - 1) % p->size;
		dif++;
		if (p->nums[i] < menor)
		{
			menor = p->nums[i];
			index = dif;
		}
	}
	return (index);
}

void	selection_sort(t_state *data)
{
	int	index;
	int	op;
	int	reps;
	t_stack *a;
	t_stack *b;
	
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
		if (index > (a->size / 2))
		{
			op = RRA;
			index = (a->size - index);
		}
		while (index--)
			operation(data, op);
		operation(data, PB);
	}
	while (b->size)
		operation(data, PA);
}
