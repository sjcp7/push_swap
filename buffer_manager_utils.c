
#include "push_swap.h"

int	is_canceled(t_operation a, t_operation b)
{
	if (a == b && (a == SA || a == SB || a == SS))
		return (1);
	if ((a == PA && b == PB) || (a == PB && b == PA))
		return (1);
	if ((a == RA && b == RRA) || (a == RRA && b == RA))
		return (1);
	if ((a == RB && b == RRB) || (a == RRB && b == RB))
		return (1);
	if ((a == RR && b == RRR) || (a == RRR && b == RR))
		return (1);
	return (0);
}

int	is_merged(t_operation a, t_operation b, t_operation *out)
{
	if ((a == SA && b == SB) || (a == SB && b == SA))
		*out = SS;
	else if ((a == RA && b == RB) || (a == RB && b == RA))
		*out = RR;
	else if ((a == RRA && b == RRB) || (a == RRB && b == RRA))
		*out = RRR;
	else if (a == RR && b == RRA)
		*out = RB;
	else if (a == RR && b == RRB)
		*out = RA;
	else if (a == RRR && b == RA)
		*out = RRB;
	else if (a == RRR && b == RB)
		*out = RRA;
	else
		return (0);
	return (1);
}

static int	next_valid(t_ops_buff *buffer, int i)
{
	while (i < buffer->size && buffer->ops[i] == NONE)
		i++;
	return (i);
}

int	buffer_simplify(t_ops_buff *buffer)
{
	t_operation	merged;
	int			i;
	int			j;
	int			changed;

	changed = 0;
	i = next_valid(buffer, 0);
	while (i < buffer->size)
	{
		j = next_valid(buffer, i + 1);
		if (j >= buffer->size)
			break ;
		merged = NONE;
		if (is_canceled(buffer->ops[i], buffer->ops[j])
			|| is_merged(buffer->ops[i], buffer->ops[j], &merged))
		{
			buffer->ops[i] = merged;
			buffer->ops[j] = NONE;
			changed = 1;
		}
		i = j;
	}
	return (changed);
}
