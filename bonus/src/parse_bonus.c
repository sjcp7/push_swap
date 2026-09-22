/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 15:27:48 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/22 12:24:44 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap_bonus.h"

static void	selecter(t_bench *bench, char *av)
{
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
		bench->strategy = -1;
}

static int	ft_add(t_stack *a, char *num)
{
	long	atoi;
	int		sign;
	int		i;

	sign = 1;
	atoi = 0;
	if (num == NULL || a == NULL)
		return (0);
	if (a->size >= a->capacity)
		ps_realloc(a);
	if (a->nums == NULL)
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
	if (ps_strcmp("--bench", av[i]) == 0)
		data->bench.visible = i++;
	if (ac - i >= 1 && ft_strncmp("--", av[i], 2) == 0)
		selecter(&data->bench, av[i++]);
	if (ac - i < 1 || data->bench.strategy == -1)
		return (ps_abort(data));
	return (i);
}

static int	fill_array(t_state *data, int ac, int i, char **av)
{
	int		x;
	char	**vnum;

	while (i < ac)
	{
		vnum = ft_split(av[i], ' ');
		x = 0;
		while (vnum[x])
		{
			if (!ft_add(data->a, vnum[x]))
			{
				while (vnum[x])
					free(vnum[x++]);
				free(vnum);
				return (ps_abort(data));
			}
			free(vnum[x++]);
		}
		free(vnum);
		i++;
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
