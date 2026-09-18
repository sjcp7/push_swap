/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 15:12:07 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/18 16:40:03 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	swap(t_stack *pilha)
{
	int	swap;
	int	i;

	if (pilha == NULL || pilha->size < 2)
		return ;
	i = ps_next(pilha);
	swap = pilha->nums[pilha->head];
	pilha->nums[pilha->head] = pilha->nums[i];
	pilha->nums[i] = swap;
}

void	re_rotate(t_stack *p)
{
	if (p == NULL || p->size < 2)
		return ;
	p->head = ps_prev(p);
}

void	rotate(t_stack *p)
{
	if (p == NULL || p->size < 2)
		return ;
	p->head = ps_next(p);
}

void	push(t_stack *dst, t_stack *src)
{
	int	i;
	int	tmp;

	if (src->size == 0)
		return ;
	i = src->head;
	tmp = src->nums[i];
	while (i < src->size - 1)
	{
		src->nums[i] = src->nums[i + 1];
		i++;
	}
	src->size--;
	i = dst->size;
	while (i > dst->head)
	{
		dst->nums[i] = dst->nums[i - 1];
		i--;
	}
	dst->nums[dst->head] = tmp;
	dst->size++;
}

void	operation(t_state *data, int ops)
{
	if (ops == SA)
		swap(data->a);
	else if (ops == SB)
		swap(data->b);
	else if (ops == SS)
	{
		swap(data->a);
		swap(data->b);
	}
	else if (ops == PA)
		push(data->a, data->b);
	else if (ops == PB)
		push(data->b, data->a);
	else if (ops == RA)
		rotate(data->a);
	else if (ops == RB)
		rotate(data->b);
	else if (ops == RR)
	{
		rotate(data->a);
		rotate(data->b);
	}
	else if (ops == RRA)
		re_rotate(data->a);
	else if (ops == RRB)
		re_rotate(data->b);
	else if (ops == RRR)
	{
		re_rotate(data->a);
		re_rotate(data->b);
	}
	else
		return ;
	ps_add_buffer(&data->bch, ops);
}
