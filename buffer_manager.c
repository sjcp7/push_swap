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

static void	buffer_manager(t_ops_buff *buffer)
{

}

static int	buffer_realloc(t_ops_buff *buffer)
{
	int	i;
	t_operation *tmp;

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

int	buffer_push(t_ops_buff *buffer, t_operation op)
{
	if (buffer->size >= buffer->capacity)
		if (!buffer_realloc(buffer))
			return (0);
	buffer->op[buffer->size] = op;
	buffer->size++;
}

void	buffer_flush(t_ops_buff *buffer)
{
	buffer_manager(buffer);
}
