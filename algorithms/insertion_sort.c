/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 10:35:51 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/18 12:53:20 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/push_swap.h"

void	insertion_sort(t_state *data)
{
	t_stack *a;
	t_stack *b;

	a = data->a;
	b = data->b;
	while (a->size)
	{
		find_posix(data, a->nums[a->head]);
		operation(data, PB);
	}
	find_max(data);
	while (b->size)
		operation(data, PA);
}

