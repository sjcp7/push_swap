/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_three.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 12:27:11 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/18 14:59:59 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	find_in_front(t_stack *b, int num)
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
		i = (i + 1) % b->size;
		next = b->nums[i];
		if (next >= maior || num > next)
			return (index + 1);
		index++;
		maior = b->nums[i];
	}
	return (index);
}

int	find_in_back(t_stack *b, int num)
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
		if (i == 0)
			i = b->size;
		i = (i - 1) % b->size;
		prev = b->nums[i];
		if (prev <= menor || num < prev)
			return(index);
		index++;
		menor = b->nums[i];
	}
	return (index);
}

void	find_posix(t_state *data, int num)
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

void	find_max(t_state *data)
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
	x = RB;
	if (index >= (b->size / 2))
	{
		x = RRB;
		index = (b->size - index);
	}
	while (index--)
		operation(data, x);
}

int	ps_sqrt(int num)
{
	int	i;
	int	valor;
	int	valor_prev;

	if (num <= 0)
		return (0);
	i = 2;
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
