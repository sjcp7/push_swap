/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 10:35:51 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/18 12:42:43 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/push_swap.h"

static int	find_in_front(t_stack *b, int num)
{
	int	i;
	int 	x;
	int	next;
	int	maior;
	int	index;
	
	index = 0;
	i = b->head;
	x = b->size;
	maior = b->nums[i];
	while (maior > num)
	{
		if (i == 0)
			i = b->size;
		i = (i - 1) % b->size;
		next = b->nums[i];
		if (next >= maior || num > next)
			return (index + 1);
		index++;
		maior = b->nums[i];
	}
	return (index);
}

static int	find_in_back(t_stack *b, int num)
{
	int	index;
	int	prev;
	int	x;
	int	menor;
	int	i;
	
	index = 0;
	i = b->head;
	x = b->size;
	menor = b->nums[i];
	while (menor < num)
	{	
		i = (i + 1) % b->size;
		prev = b->nums[i];
		if (prev <= menor || num < prev)
			return(index);
		index++;
		menor = b->nums[i];
	}
	return (index);
}

static void	find_posix(t_state *data, int num)
{
	int	i;
	int	index;
	int	op;
	t_stack	*b;

	b = data->b;
	if (b->size == 0)
		return ;
	i = b->head;
	if (b->nums[i] > num)
	{
		op = RB;
		index = find_in_front(b, num);
		if (index > (b->size / 2))
		{
			op = RRB;
			index = (b->size - index);
		}
	}
	else
	{
		op = RRB;
		index = find_in_back(b, num);
		if (index > (b->size / 2))
		{
			op = RB;
			index = (b->size - index);
		}
	}
	while (index--)
		operation(data, op);
}

static void	find_max(t_state *data)
{
	int	i;
	int	index;
	int	x;
	t_stack *b;

	b = data->b;
	i = b->head;
	x = b->size - 1;
	index = 0;
	while (b->nums[i] != x)
	{
		index++;
		i = (i + 1) % b->size;
	}
	x = RRB;
	if (index >= (b->size / 2))
	{
		x = RB;
		index = (b->size - index);
	}
	while (index--)
		operation(data, x);
}

void	insertion_sort(t_state *data)
{
	t_stack *a;
	t_stack *b;

	a = data->a;
	b = data->b;
	while (a->size)
	{
		find_posix(data, a->nums[a->head]);
		operation(data, PB);
	}
	find_max(data);
	while (b->size)
		operation(data, PA);
}

