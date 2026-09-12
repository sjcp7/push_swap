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
	if (data.bch.strategy == 1)
		selection_sort(&data);
	else if (data.bch.strategy == 2)
		bucket_sort(&data);
	else if (data.bch.strategy == 3)
		radix_sort(&data);
	//preformer_operations(&data.bch);
	if (data.bch.visible)
		ft_print_bench(&data.bch);
}
