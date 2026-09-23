/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 15:27:48 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/22 12:44:09 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ps_abort(t_state *data)
{
	ps_free(data);
	write(2, "Error\n", 6);
	return (0);
}

int	ps_realloc(t_stack *p)
{
	int	*tmp;
	int	capacity;
	int	i;

	if (p == NULL)
		return (0);
	capacity = p->capacity * 2;
	if (capacity == 0)
		capacity = 1;
	tmp = (int *)malloc(capacity * sizeof(int));
	if (tmp == NULL)
		return (0);
	i = p->size;
	while (i--)
		tmp[i] = p->nums[i];
	free(p->nums);
	p->nums = tmp;
	p->capacity = capacity;
	return (1);
}

int	normalizer(t_stack *a)
{
	int	*cpy;
	int	i;
	int	j;

	cpy = (int *)malloc(sizeof(int) * a->size);
	if (cpy == NULL)
		return (0);
	ft_memmove(cpy, a->nums, (a->size * sizeof(int)));
	if (!ps_merge_sort(cpy, 0, a->size - 1))
	{
		free(cpy);
		return (0);
	}
	i = 0;
	while (i < a->size)
	{
		j = 0;
		while (cpy[j] != a->nums[i])
			j++;
		a->nums[i++] = j;
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

	if (!a || a->size < 2)
		return (0);
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
	return ((float) mistakes / (float) pairs);
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
