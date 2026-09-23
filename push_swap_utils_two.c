/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 11:09:57 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/22 12:44:09 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ps_prev(t_stack *p)
{
	if (p == NULL || p->size == 0)
		return (0);
	if (p->head == 0)
		return (p->size - 1);
	return ((p->head - 1) % p->size);
}

int	ps_next(t_stack *p)
{
	if (p == NULL || p->size == 0)
		return (0);
	return ((p->head + 1) % p->size);
}

char	*get_op_name(t_operation op)
{
	if (op == SA)
		return ("sa");
	if (op == SB)
		return ("sb");
	if (op == SS)
		return ("ss");
	if (op == PA)
		return ("pa");
	if (op == PB)
		return ("pb");
	if (op == RA)
		return ("ra");
	if (op == RB)
		return ("rb");
	if (op == RR)
		return ("rr");
	if (op == RRA)
		return ("rra");
	if (op == RRB)
		return ("rrb");
	if (op == RRR)
		return ("rrr");
	return (NULL);
}

static void	make_operations(t_state *data, t_operation ops)
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
}

int	operation(t_state *data, t_operation ops)
{
	make_operations(data, ops);
	if (ops == RRB)
		re_rotate(data->b);
	else if (ops == RRR)
	{
		re_rotate(data->a);
		re_rotate(data->b);
	}
	if (buffer_push(&data->buffer, ops) == 0)
		return (ps_abort(data));
	return (1);
}
