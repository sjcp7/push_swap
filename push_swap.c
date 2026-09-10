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

#include "push_swap.h"

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

static int	compute_strategy(t_state *data)
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
