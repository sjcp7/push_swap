/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 12:19:25 by ljanuari          #+#    #+#             */
/*   Updated: 2026/07/31 15:12:31 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*src;
	unsigned char		a;

	src = (const unsigned char *)s;
	a = (unsigned char)c;
	if (s == NULL)
		return (NULL);
	while (n--)
	{
		if (*src == a)
			return ((void *)src);
		else
			src++;
	}
	return (NULL);
}
