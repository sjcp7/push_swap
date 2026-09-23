/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 15:03:44 by samupedr          #+#    #+#             */
/*   Updated: 2026/09/22 15:44:13 by ljanuari         ###   ########.fr       */
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
	float	disorder;
	int		visible;
	int		strategy;
	int		adaptive;
	int		total_ops;
	int		sa;
	int		sb;
	int		ss;
	int		pa;
	int		pb;
	int		ra;
	int		rb;
	int		rr;
	int		rra;
	int		rrb;
	int		rrr;
}	t_bench;

typedef enum s_operation
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

typedef struct s_ops_buff
{
	t_operation	*ops;
	int			size;
	int			capacity;
}	t_ops_buff;

typedef struct s_state
{
	t_stack		*a;
	t_stack		*b;
	t_ops_buff	buffer;
	t_bench		bench;
}	t_state;

int			ps_abort(t_state *data);
int			ps_next(t_stack *p);
int			ps_prev(t_stack *p);
int			ps_strcmp(const char *s1, const char *s2);
int			ps_atoi(const char *num, long *atoi);
int			parse(t_state *data, int ac, char **av);
int			ps_sqrt(int num);
int			find_posix(t_state *data, int num);
int			find_max(t_state *data);
int			compute_strategy(t_state *data);
int			normalizer(t_stack *a);
void		reverse_op(int *index, int size, t_operation *op);
int			ps_realloc(t_stack *p);
void		ps_print_bench(t_bench bench);
int			ps_merge_sort(int *nums, int l, int r);
void		swap(t_stack *pilha);
void		rotate(t_stack *p);
void		re_rotate(t_stack *p);
void		push(t_stack *dst, t_stack *src);
// my implementations
void	selection_sort(t_state *data);
void	chunk_sort(t_state *data);
void	radix_sort(t_state *data);
//
int			operation(t_state *data, t_operation ops);
// BUFFER_MANAGER FUNCTIONS
int			buffer_push(t_ops_buff *buffer, t_operation op);
void		buffer_flush(t_state *data);
char		*get_op_name(t_operation op);
int			is_canceled(t_operation a, t_operation b);
int			is_merged(t_operation a, t_operation b, t_operation *out);
int			buffer_simplify(t_ops_buff *buffer);
#endif
