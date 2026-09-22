/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_three.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 12:27:11 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/22 12:44:09 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_in_front(t_stack *b, int num)
{
	int	i;
	int	next;
	int	maior;
	int	index;

	index = 0;
	i = b->head;
	maior = b->nums[i];
	while (maior > num)
	{
		i = (i + 1) % b->size;
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
	int	menor;
	int	i;

	index = 0;
	i = b->head;
	menor = b->nums[i];
	while (menor < num)
	{
		if (i == 0)
			i = b->size;
		i = (i - 1) % b->size;
		prev = b->nums[i];
		if (prev <= menor || num < prev)
			return (index);
		index++;
		menor = b->nums[i];
	}
	return (index);
}

void	find_posix(t_state *data, int num)
{
	int			index;
	t_operation	op;
	t_stack		*b;

	b = data->b;
	if (b->size == 0)
		return ;
	if (b->nums[b->head] > num)
	{
		op = RB;
		index = find_in_front(b, num);
		reverse_op(&index, b->size, &op);
	}
	else
	{
		op = RRB;
		index = find_in_back(b, num);
		reverse_op(&index, b->size, &op);
	}
	while (index--)
		operation(data, op);
}

void	find_max(t_state *data)
{
	int			index;
	int			find;
	int			i;
	t_operation	op;
	t_stack		*b;

	b = data->b;
	find = b->size - 1;
	index = 0;
	i = b->head;
	while (b->nums[i] != find)
	{
		index++;
		i = (i + 1) % b->size;
	}
	op = RB;
	if (index >= (b->size / 2))
	{
		op = RRB;
		index = (b->size - index);
	}
	while (index--)
		operation(data, op);
}

int	ps_sqrt(int num)
{
	int	i;
	int	valor;
	int	valor_prev;

	if (num <= 0)
		return (0);
	i = 1;
	while (i * i < num)
		i++;
	if (i * i == num)
		return (i);
	valor = (i * i) - num;
	valor_prev = num - ((i - 1) * (i - 1));
	if (valor_prev > valor)
		return (i);
	return (i - 1);
}
