/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 15:27:48 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/10 17:33:46 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_abort(t_state *data)
{
	if (data != NULL)
	{
		if (data->a != NULL)
		{
			free(data->a->nums);
			free(data->a);
		}
		if (data->b != NULL)
		{
			free(data->b->nums);
			free(data->b);
		}
	}
	write(2, "Error\n", 6);
	return (0);
}

static void	ft_realloc(t_stack *p)
{
	int	*tmp;
	int	i;

	if (p == NULL)
		return ;
	p->capacity *= 2;
	i = p->size;
	if (p->capacity == 0)
	{
		p->nums = (int *)malloc(sizeof(int));
		p->capacity = 1;
		return ;
	}
	tmp = (int *)malloc(p->capacity * sizeof(int));	
	if (tmp == NULL)
		return ;
	while (i--)
		tmp[i] = p->nums[i];
	free(p->nums);
	p->nums = tmp;
}

static void	selecter(t_bench *bch, char *av)
{
	if (ft_strncmp("--simple", av, ft_strlen(av)) == 0)
		bch->strategy = 1;
	else if (ft_strncmp("--medium", av, ft_strlen(av)) == 0)
		bch->strategy = 2;
	else if (ft_strncmp("--complex", av, ft_strlen(av)) == 0)
		bch->strategy = 3;
	else if (ft_strncmp("--adaptive", av, ft_strlen(av)) == 0)
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
	if (a->size >= a->capacity)
		ft_realloc(a);
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

int	parse(t_state *data, int ac, char *av[])
{
	char	**vnum;
	int	i;
	int	x;

	i = 1;
	ft_bzero(data, sizeof(t_state));
	data->a = (t_stack *) malloc(sizeof(t_stack));
	data->b = NULL;
	if (data->a == NULL)
		return (ft_abort(NULL));
	ft_bzero(data->a, sizeof(t_stack));
	if (ft_strncmp("--bench", av[i], ft_strlen(av[i])) == 0)
		data->bch.visible = i++;
	if (ac - i >= 1 && ft_strncmp("--", av[i], 2) == 0)
		selecter(&data->bch, av[i++]);
	if (ac - i < 1 || data->bch.strategy < 0)
		ft_abort(data);
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
				return (ft_abort(data));
			}
			free(vnum[x++]);
		}
		free(vnum);
		i++;
	}
	data->b = (t_stack *) malloc(sizeof(t_stack));
	if (data->b == NULL)
		return (ft_abort(data));
	ft_bzero(data->b, sizeof(t_stack));
	data->b->nums = ft_calloc(data->a->capacity, sizeof(int));
	if (data->b->nums == NULL)
		return (ft_abort(data));
	data->a->head = data->a->size - 1;
	data->b->capacity = data->a->capacity;
	return (1);
}
