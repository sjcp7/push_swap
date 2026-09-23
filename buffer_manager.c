/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 14:19:08 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/22 16:47:19 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	buffer_realloc(t_ops_buff *buffer)
{
	int			i;
	t_operation	*tmp;

	buffer->capacity *= 2;
	if (buffer->capacity == 0)
	{
		buffer->ops = (t_operation *) malloc(sizeof(t_operation));
		buffer->capacity = 1;
		if (buffer->ops == NULL)
			return (0);
		return (1);
	}
	i = buffer->size;
	tmp = (t_operation *) malloc(buffer->capacity * sizeof(t_operation));
	if (tmp == NULL)
	{
		free(buffer->ops);
		return (0);
	}
	while (i--)
		tmp[i] = buffer->ops[i];
	free(buffer->ops);
	buffer->ops = tmp;
	return (1);
}

static int	*op_counter(t_bench *bench, t_operation op)
{
	if (op == SB)
		return (&bench->sb);
	if (op == SS)
		return (&bench->ss);
	if (op == PA)
		return (&bench->pa);
	if (op == PB)
		return (&bench->pb);
	if (op == RA)
		return (&bench->ra);
	if (op == RB)
		return (&bench->rb);
	if (op == RR)
		return (&bench->rr);
	if (op == RRA)
		return (&bench->rra);
	if (op == RRB)
		return (&bench->rrb);
	if (op == RRR)
		return (&bench->rrr);
	return (&bench->sa);
}

int	buffer_push(t_ops_buff *buffer, t_operation op)
{
	if (buffer->size >= buffer->capacity)
		if (!buffer_realloc(buffer))
			return (0);
	buffer->ops[buffer->size] = op;
	buffer->size++;
	return (1);
}

void	buffer_flush(t_state *data)
{
	int			*counter;
	int			i;
	t_ops_buff	*buffer;

	buffer = &data->buffer;
	while (buffer_simplify(buffer))
		;
	i = 0;
	while (i < buffer->size)
	{
		if (buffer->ops[i] != NONE)
		{
			ft_putendl_fd(get_op_name(buffer->ops[i]), 1);
			counter = op_counter(&data->bench, buffer->ops[i]);
			(*counter)++;
			data->bench.total_ops++;
		}
		i++;
	}
	buffer->size = 0;
}
