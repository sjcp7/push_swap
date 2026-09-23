/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 15:27:48 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/22 19:53:19 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	selecter(t_bench *bench, char *av, int *selected)
{
	if (ps_strcmp("--bench", av) == 0)
	{
		if (bench->visible)
			return (0);
		bench->visible = 1;
		return (1);
	}
	if (*selected)
		return (0);
	*selected = 1;
	bench->adaptive = 0;
	if (ps_strcmp("--simple", av) == 0)
		bench->strategy = 1;
	else if (ps_strcmp("--medium", av) == 0)
		bench->strategy = 2;
	else if (ps_strcmp("--complex", av) == 0)
		bench->strategy = 3;
	else if (ps_strcmp("--adaptive", av) == 0)
		bench->adaptive = 1;
	else
		return (0);
	return (1);
}

static int	ft_add(t_stack *a, char *num)
{
	long	atoi;
	int		i;

	atoi = 0;
	if (num == NULL || a == NULL)
		return (0);
	if (a->size >= a->capacity && !ps_realloc(a))
		return (0);
	if (ps_atoi(num, &atoi) == 0)
		return (0);
	i = 0;
	while (i < a->size)
		if (atoi == a->nums[i++])
			return (0);
	a->nums[a->size++] = atoi;
	return (1);
}

static int	initialization_of_store(t_state *data, int ac, char **av)
{
	int	i;
	int	selected;

	i = 1;
	ft_bzero(data, sizeof(t_state));
	data->a = (t_stack *) malloc(sizeof(t_stack));
	if (data->a == NULL)
		return (ps_abort(data));
	data->b = (t_stack *) malloc(sizeof(t_stack));
	if (data->b == NULL)
		return (ps_abort(data));
	ft_bzero(data->a, sizeof(t_stack));
	data->a->nums = NULL;
	ft_bzero(data->b, sizeof(t_stack));
	data->b->nums = NULL;
	data->bench.adaptive = 1;
	selected = 0;
	while (i < ac && ft_strncmp("--", av[i], 2) == 0)
		if (!selecter(&data->bench, av[i++], &selected))
			return (ps_abort(data));
	if (ac - i < 1)
		return (ps_abort(data));
	return (i);
}

static int	fill_array(t_state *data, int ac, int i, char **av)
{
	int		x;
	int		ok;
	char	**vnum;

	while (i < ac)
	{
		vnum = ft_split(av[i++], ' ');
		if (vnum == NULL)
			return (ps_abort(data));
		ok = (vnum[0] != NULL);
		x = 0;
		while (vnum[x])
		{
			if (ok && !ft_add(data->a, vnum[x]))
				ok = 0;
			free(vnum[x++]);
		}
		free(vnum);
		if (!ok)
			return (ps_abort(data));
	}
	return (1);
}

int	parse(t_state *data, int ac, char **av)
{
	int		i;

	i = initialization_of_store(data, ac, av);
	if (i == 0 || fill_array(data, ac, i, av) == 0)
		return (0);
	data->b->nums = ft_calloc(data->a->capacity, sizeof(int));
	if (data->b->nums == NULL || normalizer(data->a) == 0)
		return (ps_abort(data));
	data->a->head = 0;
	data->b->capacity = data->a->capacity;
	return (1);
}
