/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 10:56:47 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/22 12:44:09 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	fill_array(int *array, int *nums, int n, int i)
{
	int	k;

	k = 0;
	while (k < n)
		array[k++] = nums[i++];
}

static void	merge_arrays(int *nums, int *l_arr, int *r_arr, int sizes[3])
{
	int	i;
	int	k;
	int	l;

	i = 0;
	k = 0;
	l = sizes[2];
	while (i < sizes[0] && k < sizes[1])
	{
		if (l_arr[i] < r_arr[k])
			nums[l++] = l_arr[i++];
		else
			nums[l++] = r_arr[k++];
	}
	while (i < sizes[0])
		nums[l++] = l_arr[i++];
	while (k < sizes[1])
		nums[l++] = r_arr[k++];
}

void	merge(int *nums, int l, int m, int r)
{
	int	*left_array;
	int	*righ_array;
	int	sizes[3];

	sizes[0] = m - l + 1;
	sizes[1] = r - m;
	sizes[2] = l;
	left_array = (int *)malloc(sizeof(int) * sizes[0]);
	righ_array = (int *)malloc(sizeof(int) * sizes[1]);
	if (righ_array == NULL || left_array == NULL)
		return ;
	fill_array(left_array, nums, sizes[0], sizes[2]);
	fill_array(righ_array, nums, sizes[1], m + 1);
	merge_arrays(nums, left_array, righ_array, sizes);
	free(righ_array);
	free(left_array);
}

void	ps_merge_sort(int *nums, int l, int r)
{
	int	m;

	if (nums == NULL)
		return ;
	if (l < r)
	{
		m = l + (r - l) / 2;
		ps_merge_sort(nums, l, m);
		ps_merge_sort(nums, m + 1, r);
		merge(nums, l, m, r);
	}
}
