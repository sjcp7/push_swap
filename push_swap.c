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

int	main(int ac, char **av)
{
	t_state	data;

	if (ac < 2 || !parse(&data, ac, av))
		return (0);
	data.bench.strategy = compute_strategy(&data);
	if (data.bench.strategy == 1)
		selection_sort(&data);
	else if (data.bench.strategy == 2)
		chunk_sort(&data);
	else if (data.bench.strategy == 3)
		radix_sort(&data);
	buffer_flush(&data);
	free(data.buffer.ops);
	if (data.bench.visible)
		ps_print_bench(data.bench);
	free(data.a->nums);
	free(data.a);
	free(data.b->nums);
	free(data.b);
}
