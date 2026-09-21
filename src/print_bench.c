/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bench.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 12:39:50 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/21 12:39:55 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/push_swap.h"

static int	ps_arredondar(int num, int precision)
{
	int	pivot;

	pivot = 1;
	while (precision--)
		pivot *= 10;
	if (pivot == 1)
		return (0);
	while (num > pivot)
	{
		if ((num % 10) >= 5)
			num = (num / 10) + 1;
		else
			num = num / 10;
	}
	return (num);
}

static void	print_float(float disorder)
{
	long	int_part;
	long	decimal_part;

	disorder *= 100;
	int_part = disorder;
	disorder -= int_part;
	disorder *= 100000;
	decimal_part = disorder;
	decimal_part = ps_arredondar(decimal_part, 2);
	ft_putnbr_fd(int_part, 2);
	ft_putchar_fd('.', 2);
	ft_putnbr_fd(decimal_part, 2);
}

static char	*str_strategy(t_bench bench)
{
	if (bench.adaptive)
	{
		if (bench.strategy == 1)
			return ("Adaptive / O(n²)");
		if (bench.strategy == 2)
			return ("Adaptive / O(n√n)");
		if (bench.strategy == 3)
			return ("Adaptive / O(nlogn)");
	}
	if (bench.strategy == 1)
		return ("Simple / O(n²)");
	if (bench.strategy == 2)
		return ("medium / O(n√n)");
	if (bench.strategy == 3)
		return ("complex / O(nlogn)");
	return (NULL);
}

void	ps_print_bench_auxiliar(t_bench bench)
{
	ft_putstr_fd("[bench] ra: ", 2);
	ft_putnbr_fd(bench.ra, 2);
	ft_putstr_fd(" rb: ", 2);
	ft_putnbr_fd(bench.rb, 2);
	ft_putstr_fd(" rr: ", 2);
	ft_putnbr_fd(bench.rr, 2);
	ft_putstr_fd(" rra: ", 2);
	ft_putnbr_fd(bench.rra, 2);
	ft_putstr_fd(" rrb: ", 2);
	ft_putnbr_fd(bench.rrb, 2);
	ft_putstr_fd(" rrr: ", 2);
	ft_putnbr_fd(bench.rrr, 2);
	ft_putchar_fd('\n', 2);
}

void	ps_print_bench(t_bench bench)
{
	ft_putstr_fd("[bench] disorder: ", 2);
	print_float(bench.disorder);
	ft_putendl_fd("%", 2);
	ft_putstr_fd("[bench] strategy: ", 2);
	ft_putendl_fd(str_strategy(bench), 2);
	ft_putstr_fd("[bench] total_ops: ", 2);
	ft_putnbr_fd(bench.total_ops, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("[bench] sa: ", 2);
	ft_putnbr_fd(bench.sa, 2);
	ft_putstr_fd(" sb: ", 2);
	ft_putnbr_fd(bench.sb, 2);
	ft_putstr_fd(" ss: ", 2);
	ft_putnbr_fd(bench.ss, 2);
	ft_putstr_fd(" pa: ", 2);
	ft_putnbr_fd(bench.pa, 2);
	ft_putstr_fd(" pb: ", 2);
	ft_putnbr_fd(bench.pb, 2);
	ft_putchar_fd('\n', 2);
	ps_print_bench_auxiliar(bench);
}
