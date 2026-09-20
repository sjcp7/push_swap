/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 15:27:48 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/17 11:49:11 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ps_abort(t_state *data)
{
	if (data != NULL)
	{
		if (data->a != NULL)
		{
			if (data->a->nums)
				free(data->a->nums);
			free(data->a);
		}
		if (data->b != NULL)
		{
			if (data->b->nums)
				free(data->b->nums);
			free(data->b);
		}
	}
	write(2, "Error\n", 6);
	return (0);
}

void	ps_realloc(t_stack *p)
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

int	normalizer(t_stack *a)
{
	int	*cpy;
	int	x;
	int	i;
	int	j;
		
	cpy = (int *)malloc(sizeof(int) * a->size);
	if (cpy == NULL)
		return (0);
	ft_memmove(cpy, a->nums, (a->size * sizeof(int)));
	ps_merge_sort(cpy, 0, a->size - 1);
	x = a->size;
	j = 0;
	while (j < x)
	{
		i = -1;
		while (++i < x)
			if (a->nums[i] == cpy[j])
				break ;
		a->nums[i] = j++;
	}
	free(cpy);
	return (1);
}

static float	calc_disorder(t_stack *a)
{
	int	mistakes;
	int	pairs;
	int	i;
	int	j;
	
	if (!a || a->size == 0)
		return (-1);
	pairs = a->size * (a->size - 1) / 2;
	mistakes = 0;
	i = 0;
	while (i < a->size)
	{
		j = i + 1;
		while (j < a->size)
			if (a->nums[i] > a->nums[j++])
				mistakes += 1;
		i++;
	}
	return ((float)mistakes /(float)pairs);
}

int	compute_strategy(t_state *data)
{
	float	disord;

	data->bench.disorder = calc_disorder(data->a);
	if (data->bench.strategy)
		return (data->bench.strategy);
	disord = data->bench.disorder;
	if (disord < 0.2)
		return (1);
	if (disord < 0.5)
		return (2);
	return (3);
}
