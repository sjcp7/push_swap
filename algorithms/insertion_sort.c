
// this project was did by leosnane januario
// leosnanej@gmail.com
// 12/09/2026

#include "../includes/push_swap.h"

// this is a insertion_sort adaptation for a staks
// it works like two hand of cards, one hand is sorted and another one isn't yet, so you can take any card from unsoted hand and put in right position in a sorted hand, you need to find where is the right position in a sorted hand, make rotates (or reverse_rotates if it's more apropriet) and push the value to right position in a sorted hand
//

static int	find_in_front(t_stack *b, int num)
{
	int	i;
	int 	x;
	int	prev;
	int	maior;
	int	index;
	
	index = 0;
	i = b->head;
	x = b->size;
	maior = b->nums[i];
	while (maior > num && x--)
	{
		ft_printf("[%d] > [%d]\n", maior, num);
		index++;
		if (i == 0)
			i = b->size;
		i = (i - 1) % b->size;
		prev = b->nums[i];
		if (prev > maior)
			break ;
		maior = b->nums[i];
	}
	return (index);
}

static int	find_in_back(t_stack *b, int num)
{
	int	index;
	int	prev;
	int	x;
	int	menor;
	int	i;
	
	index = 0;
	i = b->head;
	x = b->size;
	menor = b->nums[i];
	while (menor < num && x--)
	{
		ft_printf("[%d] < [%d]\n", b->nums[i], num);
		index++;	
		i = (i + 1) % b->size;
		prev = b->nums[i];
		if (prev < menor)
			break ;
		menor = b->nums[i];
	}
	return (index * -1);
}

static int	find_posix(t_stack *b, int num)
{
	int	i;
	int	(*way)(t_stack *, int);
	
	if (b->size == 0)
		return (0);
	i = b->head;
	way = &find_in_back;
	if (b->nums[i] > num)
		way = &find_in_front;
	return (way(b, num));
}

static int	find_max(t_stack *b)
{
	int	i;
	int	index;
	int	x;
	int	prev;

	i = b->head;
	x = b->size;
	prev = b->nums[i];
	i = ps_next(b);
	index = 0;
	while (prev < b->nums[i])
	{
		index++;
		prev = b->nums[i];
		if (i == 0)
			i = b->size;
		i = (i - 1) % b->size;
	}
	return (index);
}

void	insertion_sort(t_state *data)
{
	t_stack *a;
	t_stack *b;
	int	op;
	int	index;

	a = data->a;
	b = data->b;
	while (a->size)
	{
		index = find_posix(b, a->nums[a->head]);
		ft_printf("\n-[%d]-\n", index);
		op = RB;
		if (index < 0)
		{
			op = RRB;
			index *= -1;
		}
		/*if (index > (b->size / 2))
		{
			if (op == RB)
				op = RRB;
			else
				op = RB;
			index = (b->size - index);
		}*/
		while (index--)
			operation(data, op);
		operation(data, PB);
	}
	index = find_max(b);
	op = RRB;
	if (index > (b->size / 2))
	{
		op = RB;	
		index = (b->size - index);
	}
	while (index--)
		operation(data, op);
	while (b->size)
		operation(data, PA);
}

