

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
