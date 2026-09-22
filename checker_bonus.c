/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 19:47:56 by samupedr          #+#    #+#             */
/*   Updated: 2026/09/22 21:54:10 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static int	is_op(char *line, char *name)
{
	size_t	len;

	len = ft_strlen(name);
	if (ft_strlen(line) != len + 1 || line[len] != '\n')
		return (0);
	return (ft_strncmp(line, name, len) == 0);
}

static t_operation	get_op(char *line)
{
	if (is_op(line, "sa"))
		return (SA);
	if (is_op(line, "sb"))
		return (SB);
	if (is_op(line, "ss"))
		return (SS);
	if (is_op(line, "pa"))
		return (PA);
	if (is_op(line, "pb"))
		return (PB);
	if (is_op(line, "ra"))
		return (RA);
	if (is_op(line, "rb"))
		return (RB);
	if (is_op(line, "rr"))
		return (RR);
	if (is_op(line, "rra"))
		return (RRA);
	if (is_op(line, "rrb"))
		return (RRB);
	if (is_op(line, "rrr"))
		return (RRR);
	return (NONE);
}

static int	read_ops(t_state *state)
{
	char		*line;
	t_operation	op;

	line = get_next_line(0);
	while (line)
	{
		op = get_op(line);
		free(line);
		if (op == NONE)
			return (0);
		operation(state, op);
		line = get_next_line(0);
	}
	return (1);
}

static int	is_sorted(t_state *state)
{
	int	i;

	if (state->b->size != 0)
		return (0);
	i = 0;
	while (i < state->a->size - 1)
	{
		if (state->a->v[i] < state->a->v[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_state	state;

	if (argc < 2)
		return (0);
	if (!parse(&state, argc, argv) || !read_ops(&state))
		ft_putendl_fd("Error", 2);
	else if (is_sorted(&state))
		ft_putendl_fd("OK", 1);
	else
		ft_putendl_fd("KO", 1);
	vector_free(state.a);
	vector_free(state.b);
	return (0);
}
