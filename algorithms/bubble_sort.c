/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubblue_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 10:53:37 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/14 10:54:34 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	bubble_sort(t_state *data)
{
	int		reps;
	int		i;
	int	verif;
	t_stack	*a;
	t_stack	*b;
	
	a = data->a;
	b = data->b;
	while (data->a->size)
	{
		reps = a->size;
		verif = 0;
		while (reps--)
		{
			operation(data, RRA);
			i = ps_next(a);
			if (a->nums[a->head] > a->nums[i])
			{
				operation(data, SA);
				verif = 1;
			}
		}
		if (!verif)
			break ;
		operation(data, PB);
	}
	reps = b->size;
	while (reps--)
		operation(data, PA);
}
