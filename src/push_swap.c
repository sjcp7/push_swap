/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 15:20:05 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/18 16:39:54 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	main(int ac, char *av[])
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
	if (data.bench.visible)
		ps_print_bench(data.bench);
	//chunk_sort(&data);
	t_stack *test = data.a;
	ft_printf("-------- stack one -------\n");
	int i = test->size;
	int x = 1;
	while (i--)
	{
		ft_printf("%d.[%d]\n", x++, test->nums[test->head]);
		test->head = ps_next(test);
	}
	test = data.b;
	ft_printf("-------- stack two -------\n");
	i = test->size;
	x = 1;
	while (i--)
	{
		ft_printf("%d.[%d]\n", x++, test->nums[test->head]);
		test->head = ps_next(test);	
	}
	free(data.a->nums);
	free(data.a);
	free(data.b->nums);
	free(data.b);
}
