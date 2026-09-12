/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 15:03:44 by samupedr          #+#    #+#             */
/*   Updated: 2026/09/10 16:18:46 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft.h"
# include <stdlib.h>

# include <stdlib.h>

typedef struct s_stack
{
	int	*nums;
	int	head;
	int	size;
	int	capacity;
}	t_stack;

typedef struct s_bench
{
	int		disorder;
	int		visible;
	int		strategy;
	char	*ops;
	int		total_ops;
}	t_bench;

typedef struct s_state
{
    t_stack *a;
    t_stack *b;
	t_bench	bch;
}	t_state;

enum ops
{
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
};

int		ps_abort(t_state *data);
int		parse(t_state *data, int ac, char *av[]);
int		compute_strategy(t_state *data);
void    ps_realloc(t_stack *p);
void	swap(t_stack *pilha);
void	rotate(t_stack *p);
void	re_rotate(t_stack *p);
void	push(t_stack *dst, t_stack *src);
void	selection_sort(t_state *data);
void	bucket_sort(t_state *data);
void	radix_sort(t_state *data);
void	operation(t_state *data, int ops);
#endif