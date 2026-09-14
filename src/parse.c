/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 15:27:48 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/14 15:58:37 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	selecter(t_bench *bch, char *av)
{
	int	len;

	len = ft_strlen(av);
	if (len == ft_strlen("--simple"))
		;
	else if (len == ft_strlen("--medium"))
		;
	else if (len == ft_strlen("--complex"))
		;
	else if (len == ft_strlen("--adaptive"))
		;
	else
	{
		bch->strategy = -1;
		return ;
	}
	if (ft_strncmp("--simple", av, len) == 0)
		bch->strategy = 1;
	else if (ft_strncmp("--medium", av, len) == 0)
		bch->strategy = 2;
	else if (ft_strncmp("--complex", av, len) == 0)
		bch->strategy = 3;
	else if (ft_strncmp("--adaptive", av, len) == 0)
		bch->strategy = 0;
	else
		bch->strategy = -1;
}

static int	ft_add(t_stack *a, char *num)
{
	int	atoi;
	int	sign;
	int	i;

	sign = 1;
	atoi = 0;
	if (num == NULL || a == NULL)
		return (0);
	if (a->size >= a->capacity)
		ps_realloc(a);
	if (*num == '+' || *num == '-')
	{
		if (*num == '-')
			sign = -1;
		num++;
	}
	while (*num >= '0' && *num <= '9')
		atoi = (atoi * 10) + (*num++ - '0');
	if (*num != '\0' || a->nums == NULL)
		return (0);
	i = 0;
	atoi *= sign;
	while (i < a->size)
		if (atoi == a->nums[i++])
			return (0);
	a->nums[a->size++] = atoi;
	return (1);
}

static int	division_01(t_state *data, int ac, char *av[])
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
	if (ft_strncmp("--bench", av[i], ft_strlen(av[i])) == 0)
		data->bch.visible = i++;
	if (ac - i >= 1 && ft_strncmp("--", av[i], 2) == 0)
		selecter(&data->bch, av[i++]);
	if (ac - i < 1 || data->bch.strategy == -1)
		return(ps_abort(data));
	return (i);
}

static int	division_02(t_state *data)
{
	data->b->nums = ft_calloc(data->a->capacity, sizeof(int));
	if (data->b->nums == NULL)
		return (ps_abort(data));
	data->a->head = data->a->size - 1;
	data->b->capacity = data->a->capacity;
	return (1);
}

int	parse(t_state *data, int ac, char *av[])
{
	char	**vnum;
	int		i;
	int		x;
	
	i = division_01(data, ac, av);
	if (i == 0)
		return (0);
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
	return (division_02(data));
}
