/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 15:03:44 by samupedr          #+#    #+#             */
/*   Updated: 2026/09/18 13:18:27 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft.h"
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
	int		capacity;
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
	SA = 1,
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
int		ps_next(t_stack *p);
int		ps_prev(t_stack *p);
int		parse(t_state *data, int ac, char *av[]);
int		ps_sqrt(int num);
int		compute_strategy(t_state *data);
void    ps_realloc(t_stack *p);
int	normalizer(t_stack *a);
void	ps_add_buffer(t_bench *bench, int op);
void	ps_print_op(t_bench *bench);
void	ps_merge_sort(int *nums, int l, int r);
int	find_in_back(t_stack *b, int num);
int	find_in_front(t_stack *b, int num);
void	find_posix(t_state *data, int num);
void	find_max(t_state *data);
void	swap(t_stack *pilha);
void	rotate(t_stack *p);
void	re_rotate(t_stack *p);
void	push(t_stack *dst, t_stack *src);
// my implementations
void	bubble_sort(t_state *data);
void	selection_sort(t_state *data);
void	insertion_sort(t_state *data);
void	chunk_sort(t_state *data);
void	radix_sort(t_state *data);
//
void	operation(t_state *data, int ops);
#endif
