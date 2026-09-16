

#include "../includes/push_swap.h"

int	ps_next(t_stack *p)
{
	if (p == NULL || p->size == 0)
		return (-1);
	if (p->head == 0)
		return (p->size - 1); 
	return ((p->head - 1) % p->size);
}

int	ps_prev(t_stack *p)
{
	if (p == NULL || p->size == 0)
		return (-1);
	return ((p->head + 1) % p->size);
}

static void	ps_ops_alloc(t_bench *bench)
{
	char	*tmp;
	int	i;

	if (bench == NULL || bench->total_ops < bench->capacity)
		return ;
	bench->capacity *= 2;
	if (bench->capacity == 0)
	{
		bench->ops = (char *)malloc(sizeof(char));
		bench->capacity = 1;
		return ;
	}	
	tmp = (char *)ft_calloc(bench->capacity, sizeof(char));
	if (tmp == NULL)
		return ;
	i = bench->total_ops;
	while (i--)
		tmp[i] = bench->ops[i]; 
	free(bench->ops);
	bench->ops = tmp;
}

void	ps_add_buffer(t_bench *bench, int op)
{
	int	i;

	ps_ops_alloc(bench);
	i = ++bench->total_ops;
	bench->ops[i - 1] = op;
}

void	ps_print_op(t_bench *bench)
{
	int	i;

	i = 0;
	while (bench->ops[i])
	{
		if (bench->ops[i] == SA)
			ft_printf("sa\n");
		else if (bench->ops[i] == SB)
			ft_printf("sb\n");
		else if (bench->ops[i] == PA)
			ft_printf("pa\n");
		else if (bench->ops[i] == PB)
			ft_printf("pb\n");
		else if (bench->ops[i] == SS)
			ft_printf("ss\n");
		else if (bench->ops[i] == RA)
			ft_printf("ra\n");
		else if (bench->ops[i] == RB)
			ft_printf("rb\n");
		else if (bench->ops[i] == RR)
			ft_printf("rr\n");
		else if (bench->ops[i] == RRA)
			ft_printf("rra\n");
		else if (bench->ops[i] == RRB)
			ft_printf("rrb\n");
		else
			ft_printf("rrr\n");
		i++;
	}
}
