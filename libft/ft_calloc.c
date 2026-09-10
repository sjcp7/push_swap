/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 08:53:24 by ljanuari          #+#    #+#             */
/*   Updated: 2026/08/04 13:14:48 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	to_zero(void *s, size_t n)
{
	unsigned char	*src;

	src = (unsigned char *)s;
	while (n--)
		*src++ = '\0';
}

void	*ft_calloc(size_t nitems, size_t size)
{
	unsigned char	*ptr;
	size_t			max;
	size_t			total;

	max = -1;
	if (!nitems || !size)
	{
		ptr = (unsigned char *)malloc(1);
		if (!ptr)
			return (NULL);
		to_zero(ptr, 1);
		return (ptr);
	}
	if (nitems > (max / size))
		return (NULL);
	total = nitems * size;
	ptr = (unsigned char *) malloc(total);
	if (!ptr)
		return (NULL);
	to_zero(ptr, total);
	return (ptr);
}
