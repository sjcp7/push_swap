/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 12:26:22 by ljanuari          #+#    #+#             */
/*   Updated: 2026/08/04 11:05:32 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*src;
	const unsigned char	*crs;

	src = (const unsigned char *)s1;
	crs = (const unsigned char *)s2;
	if (!n || s1 == NULL || s2 == NULL)
		return (0);
	while (n--)
	{
		if (n && *src == *crs)
		{
			src++;
			crs++;
		}
		else
			break ;
	}
	return (*src - *crs);
}
