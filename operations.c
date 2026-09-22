/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 15:12:07 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/22 12:44:09 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	if (src->size != 0)
		src->head %= src->size;
	i = dst->size;
	while (i > dst->head)
	{
		dst->nums[i] = dst->nums[i - 1];
		i--;
	}
	dst->nums[dst->head] = tmp;
	dst->size++;
}
