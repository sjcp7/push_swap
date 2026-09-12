/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 15:20:05 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/10 17:13:01 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	main(int ac, char *av[])
{
	t_state	data;

	if (ac < 2 || !parse(&data, ac, av))
		return (0);
	if (!data.bch.strategy)
		data.bch.strategy = compute_strategy(&data);
/*	if (data.bch.strategy == 1)
		selection_sort(&data);
	else if (data.bch.strategy == 2)
		bucket_sort(&data);
	else if (data.bch.strategy == 3)
		radix_sort(&data);
	preformer_operations(&data.bch);
	if (data.bch.visible)
		ft_print_bench(&data.bch);*/
//
	int i = 0;
	t_stack *tast = data.a;
	//swap(tast);
	//re_rotate(tast);
	push(data.b, data.a);
	push(data.b, data.a);
	push(data.b, data.a);
	//rotate(data.b);
	push(data.a, data.b);
	push(data.a, data.b);
	push(data.a, data.b);
	while (i < tast->size)
	{
		ft_printf("%d.[%d]\n", ++i, tast->nums[tast->head]);
		if (tast->head == 0)
			tast->head = tast->size;
		tast->head = (tast->head - 1) % tast->size;
	}
	i = 0;
	tast = data.b;
	ft_printf("  ---- SPACE ---- \n");
	while (i < tast->size)
	{
		ft_printf("%d.[%d]\n", ++i, tast->nums[tast->head]);
		if (tast->head == 0)
			tast->head = tast->size;
		tast->head = (tast->head - 1) % tast->size;
	}
	free(data.a->nums);
	free(data.a);
	free(data.b->nums);
	free(data.b);

//
}
