/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 19:48:18 by samupedr          #+#    #+#             */
/*   Updated: 2026/09/22 22:01:25 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include <stdlib.h>
# include <limits.h>
# include "libft.h"
# include "get_next_line_bonus.h"

typedef struct s_vector
{
	int	*v;
	int	size;
	int	capacity;
}	t_vector;

typedef enum e_operation
{
	NONE = 0,
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR
}	t_operation;

typedef struct s_state
{
	t_vector	*a;
	t_vector	*b;
}	t_state;

t_vector	*vector_new(int capacity);
int			vector_push(t_vector *vec, int n);
void		vector_reverse(t_vector *vec);
void		vector_free(t_vector *vec);
int			parse(t_state *state, int argc, char **argv);
void		operation(t_state *state, t_operation op);

#endif
