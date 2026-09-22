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

static void	make_operations_1(t_state *data, t_operation ops)
{
	if (ops == SA)
	{
		swap(data->a);
		ft_putendl_fd("sa", 1);
		data->bench.sa++;
	}
	else if (ops == SB)
	{
		swap(data->b);
		ft_putendl_fd("sb", 1);
		data->bench.sb++;
	}
	else if (ops == SS)
	{
		swap(data->a);
		swap(data->b);
		ft_putendl_fd("ss", 1);
		data->bench.ss++;
	}
	else if (ops == PA)
	{
		push(data->a, data->b);
		ft_putendl_fd("pa", 1);
		data->bench.pa++;
	}
}

static void	make_operations_2(t_state *data, t_operation ops)
{
	if (ops == PB)
	{
		push(data->b, data->a);
		ft_putendl_fd("pb", 1);
		data->bench.pb++;
	}
	else if (ops == RA)
	{
		rotate(data->a);
		ft_putendl_fd("ra", 1);
		data->bench.ra++;
	}
	else if (ops == RB)
	{
		rotate(data->b);
		ft_putendl_fd("rb", 1);
		data->bench.rb++;
	}
	else if (ops == RR)
	{
		rotate(data->a);
		rotate(data->b);
		ft_putendl_fd("rr", 1);
		data->bench.rr++;
	}
}

void	operation(t_state *data, t_operation ops)
{
	make_operations_1(data, ops);
	make_operations_2(data, ops);
	if (ops == RRA)
	{
		re_rotate(data->a);
		ft_putendl_fd("rra", 1);
		data->bench.rra++;
	}
	else if (ops == RRB)
	{
		re_rotate(data->b);
		ft_putendl_fd("rrb", 1);
		data->bench.rrb++;
	}
	else if (ops == RRR)
	{
		re_rotate(data->a);
		re_rotate(data->b);
		ft_putendl_fd("rrr", 1);
		data->bench.rrr++;
	}
	data->bench.total_ops++;
}
