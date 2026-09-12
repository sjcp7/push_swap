/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 15:12:07 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/10 16:18:35 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	swap(t_stack *pilha)
{
	int	swap;
	int	i;

	if (pilha == NULL || pilha->size < 2)
		return ;
	i = (pilha->head - 1) % pilha->size;
	if (pilha->head == 0)
		i = pilha->size - 1;
	swap = pilha->nums[pilha->head];
	pilha->nums[pilha->head] = pilha->nums[i];
	pilha->nums[i] = swap;
}

void	re_rotate(t_stack *p)
{
	if (p == NULL || p->size < 2)
		return ;
	p->head = (p->head + 1) % p->size;
}

void	rotate(t_stack *p)
{
	if (p == NULL || p->size < 2)
		return ;
	if (p->head == 0)
		p->head = p->size;
	p->head = (p->head - 1) % p->size;
}

void	push(t_stack *dst, t_stack *src)
{
	int	i;
	int	x;
	int	tmp;

	if (src->size == 0)
		return ;
	i = src->head;
	x = i + 1;
	tmp = src->nums[i];
	while (i < src->size - 1)
		src->nums[i++] = src->nums[x++];
	src->size--;
	if (src->head == 0)
		src->head = src->size;
	if (src->size)
		src->head = (src->head - 1) % src->size;
	dst->nums[dst->size] = dst->nums[0];
	i = 0;
	x = i + 1;
	while (i < dst->head)
		dst->nums[i++] = dst->nums[x++];
	dst->nums[dst->head] = tmp;
	dst->size++;
}

void	operation(t_state *data, int ops)
{
	if (ops == SA)
		swap(data->a);
	if (ops == SB)
		swap(data->b);
	if (ops == SS)
	{
		swap(data->a);
		swap(data->b);
	}
	if (ops == PA)
		push(data->a, data->b);
	if (ops == PB)
		push(data->b, data->a);
	if (ops == RA)
		rotate(data->a);
	if (ops == RB)
		rotate(data->b);
	if (ops == RR)
	{
		rotate(data->a);
		rotate(data->b);
	}
	if (ops == RRA)
		re_rotate(data->a);
	if (ops == RRB)
		re_rotate(data->b);
	if (ops == RRR)
	{
		re_rotate(data->a);
		re_rotate(data->b);
	}
}
