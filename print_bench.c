/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bench.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 12:39:50 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/22 12:47:50 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	print_float(float disorder)
{
	long	hundredths;

	hundredths = (long)(disorder * 10000.0 + 0.5);
	ft_putnbr_fd(hundredths / 100, 2);
	ft_putchar_fd('.', 2);
	ft_putchar_fd(hundredths % 100 / 10 + '0', 2);
	ft_putchar_fd(hundredths % 10 + '0', 2);
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
