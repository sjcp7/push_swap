/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort_tests.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 10:56:47 by ljanuari          #+#    #+#             */
/*   Updated: 2026/09/14 14:30:36 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	merge(int *nums, int l, int m, int r)
{
	int	*L;
	int	*R;
	int	k;
	int	i;
	int	n;
	
	n = m - l + 1;
	L = (int *)malloc(sizeof(int) * n);
	R = (int *)malloc(sizeof(int) * (r - m));
	if (R == NULL || L == NULL)
		return ;
	k = 0;
	i = l;
	while (k < n)
		L[k++] = nums[i++];
	k = 0;
	i = m + 1;
	while (k < r - m)
		R[k++] = nums[i++];
	i = 0;
	k = 0;
	while (i < n && k < (r - m))
		if (L[i] < R[k])
			nums[l++] = L[i++];
		else
			nums[l++] = R[k++];
	while (i < n)
		nums[l++] = L[i++];
	while (k < (r - m))
		nums[l++] = R[k++];
	free(R);
	free(L);
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
