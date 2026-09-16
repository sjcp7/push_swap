/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 15:27:48 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/14 15:15:59 by ljanuari         ###   ########.fr       */
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

static int	calc_disorder(t_stack *a)
{
	int	mistakes;
	int	pairs;
	int	i;
	int	j;
	
	if (!a)
		return (-1);
	pairs = a->size * a->size;
	mistakes = 0;
	i = 0;
	if (pairs <= 0)
		return (-1);
	while (i < a->size)
	{
		j = i + 1;
		while (j < a->size)
			if (a->nums[i] > a->nums[j++])
				mistakes += 1;
		i++;
	}
	return ((mistakes * 10000) / pairs);
}

int	compute_strategy(t_state *data)
{
	int	uni;

	data->bch.disorder = calc_disorder(data->a);
	uni = data->bch.disorder / 1000;
	if (uni < 2)
		return (1);
	if (uni < 5)
		return (2);
	return (3);
}
