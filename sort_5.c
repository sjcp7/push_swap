/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 12:16:35 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/28 12:16:37 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	sort_3(t_state *data)
{
	t_stack	*a;
	int		trio[3];
	int		i;

	a = data->a;
	i = a->head;
	trio[0] = a->nums[i];
	i = (i + 1) % a->size;
	trio[1] = a->nums[i];
	i = (i + 1) % a->size;
	trio[2] = a->nums[i];
	if ((trio[0] > trio[1]) != (trio[1] > trio[2]) != (trio[0] > trio[2]))
		if (!operation(data, SA))
			return (0);
	if ((trio[0] < trio[2]) != (trio[1] < trio[2]))
		if (!operation(data, RA))
			return (0);
	if (trio[0] > trio[2] && trio[1] > trio[2])
		if (!operation(data, RRA))
			return (0);
	return (1);
}

static int	find_min(t_stack *p)
{
	int	i;
	int	dif;
	int	index;
	int	reps;
	int	menor;

	if (p->size == 0)
		return (-1);
	i = p->head;
	menor = p->nums[i];
	index = 0;
	dif = 0;
	reps = p->size;
	while (--reps)
	{
		i = (i + 1) % p->size;
		dif++;
		if (p->nums[i] < menor)
		{
			menor = p->nums[i];
			index = dif;
		}
	}
	return (index);
}

static int	push_min(t_state *data)
{
	int			index;
	t_operation	op;
	t_stack		*a;

	a = data->a;
	index = find_min(a);
	if (index == -1)
		return (0);
	op = RA;
	reverse_op(&index, a->size, &op);
	while (index--)
		if (operation(data, op) == 0)
			return (0);
	if (operation(data, PB) == 0)
		return (0);
	return (1);
}

int	sort_5(t_state *data)
{
	int	i;

	i = data->a->size - 3;
	while (data->a->size > 3)
		if (!push_min(data))
			return (0);
	if (!sort_3(data))
		return (0);
	while (i--)
		if (!operation(data, PA))
			return (0);
	return (1);
}
