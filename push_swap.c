/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 15:20:05 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/22 12:44:09 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_sorted(t_stack *a)
{
	int	i;

	i = 1;
	while (i < a->size)
	{
		if (a->nums[i - 1] > a->nums[i])
			return (0);
		i++;
	}
	return (1);
}

static int	run_sort(t_state *data)
{
	if (is_sorted(data->a))
		return (1);
	if (data->bench.strategy == 1)
		return (selection_sort(data));
	if (data->bench.strategy == 2)
		return (chunk_sort(data));
	return (radix_sort(data));
}

void	ps_free(t_state *data)
{
	if (data == NULL)
		return ;
	free(data->buffer.ops);
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

int	main(int ac, char **av)
{
	t_state	data;

	if (ac < 2 || !parse(&data, ac, av))
		return (0);
	data.bench.strategy = compute_strategy(&data);
	if (!run_sort(&data))
		return (ps_abort(&data));
	buffer_flush(&data);
	if (data.bench.visible)
		ps_print_bench(data.bench);
	ps_free(&data);
	return (0);
}
