/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 20:57:48 by samupedr          #+#    #+#             */
/*   Updated: 2026/09/22 21:11:57 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

t_vector	*vector_new(int capacity)
{
	t_vector	*vector;

	vector = (t_vector *)malloc(sizeof(t_vector));
	if (!vector)
		return (NULL);
	vector->v = NULL;
	vector->size = 0;
	vector->capacity = capacity;
	if (capacity > 0)
	{
		vector->v = (int *)malloc(sizeof(int) * capacity);
		if (!vector->v)
		{
			free(vector);
			return (NULL);
		}
	}
	return (vector);
}

static int	vector_grow(t_vector *vec)
{
	int	*buf;
	int	capacity;
	int	i;

	capacity = vec->capacity * 2;
	if (capacity == 0)
		capacity = 8;
	buf = (int *)malloc(sizeof(int) * capacity);
	if (!buf)
		return (0);
	i = 0;
	while (i < vec->size)
	{
		buf[i] = vec->v[i];
		i++;
	}
	free(vec->v);
	vec->v = buf;
	vec->capacity = capacity;
	return (1);
}

int	vector_push(t_vector *vec, int n)
{
	if (vec->size >= vec->capacity && !vector_grow(vec))
		return (0);
	vec->v[vec->size++] = n;
	return (1);
}

void	vector_reverse(t_vector *vec)
{
	int	i;
	int	tmp;

	i = 0;
	while (i < vec->size / 2)
	{
		tmp = vec->v[i];
		vec->v[i] = vec->v[vec->size - 1 - i];
		vec->v[vec->size - 1 - i] = tmp;
		i++;
	}
}

void	vector_free(t_vector *vec)
{
	if (!vec)
		return ;
	free(vec->v);
	free(vec);
}
