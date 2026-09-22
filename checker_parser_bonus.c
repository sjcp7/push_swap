/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_parser_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 20:11:01 by samupedr          #+#    #+#             */
/*   Updated: 2026/09/22 22:00:46 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static int	ps_atoi(const char *s, int *out)
{
	long	n;
	int		sign;

	n = 0;
	sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	if (!ft_isdigit(*s))
		return (0);
	while (ft_isdigit(*s))
	{
		n = n * 10 + (*s - '0');
		if (n * sign > INT_MAX || n * sign < INT_MIN)
			return (0);
		s++;
	}
	if (*s)
		return (0);
	*out = (int)(n * sign);
	return (1);
}

static int	contains(t_vector *vec, int n)
{
	int	i;

	i = 0;
	while (i < vec->size)
		if (vec->v[i++] == n)
			return (1);
	return (0);
}

static int	add_arg(t_vector *a, char *arg)
{
	char	**words;
	int		ok;
	int		n;
	int		i;

	words = ft_split(arg, ' ');
	if (!words)
		return (0);
	ok = (words[0] != NULL);
	i = 0;
	while (words[i])
	{
		if (ok && (!ps_atoi(words[i], &n) || contains(a, n)
				|| !vector_push(a, n)))
			ok = 0;
		free(words[i++]);
	}
	free(words);
	return (ok);
}

int	parse(t_state *state, int argc, char **argv)
{
	int	i;

	state->b = NULL;
	state->a = vector_new(argc);
	if (!state->a)
		return (0);
	i = 1;
	while (i < argc)
		if (!add_arg(state->a, argv[i++]))
			return (0);
	vector_reverse(state->a);
	state->b = vector_new(state->a->size);
	return (state->b != NULL);
}
