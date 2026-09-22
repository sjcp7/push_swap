/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 21:30:00 by samupedr          #+#    #+#             */
/*   Updated: 2026/09/22 21:44:34 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static void	swap(t_vector *s)
{
	int	tmp;

	if (s->size < 2)
		return ;
	tmp = s->v[s->size - 1];
	s->v[s->size - 1] = s->v[s->size - 2];
	s->v[s->size - 2] = tmp;
}

static void	push(t_vector *dst, t_vector *src)
{
	if (src->size == 0)
		return ;
	dst->v[dst->size++] = src->v[--src->size];
}

static void	rotate(t_vector *s)
{
	int	tmp;
	int	i;

	if (s->size < 2)
		return ;
	tmp = s->v[s->size - 1];
	i = s->size - 1;
	while (i > 0)
	{
		s->v[i] = s->v[i - 1];
		i--;
	}
	s->v[0] = tmp;
}

static void	reverse_rotate(t_vector *s)
{
	int	tmp;
	int	i;

	if (s->size < 2)
		return ;
	tmp = s->v[0];
	i = 0;
	while (i < s->size - 1)
	{
		s->v[i] = s->v[i + 1];
		i++;
	}
	s->v[s->size - 1] = tmp;
}

void	operation(t_state *state, t_operation op)
{
	if (op == SA || op == SS)
		swap(state->a);
	if (op == SB || op == SS)
		swap(state->b);
	if (op == PA)
		push(state->a, state->b);
	if (op == PB)
		push(state->b, state->a);
	if (op == RA || op == RR)
		rotate(state->a);
	if (op == RB || op == RR)
		rotate(state->b);
	if (op == RRA || op == RRR)
		reverse_rotate(state->a);
	if (op == RRB || op == RRR)
		reverse_rotate(state->b);
}
