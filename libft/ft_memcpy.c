/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 15:32:49 by ljanuari          #+#    #+#             */
/*   Updated: 2026/07/31 15:15:07 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*s2;
	unsigned char		*s1;

	s1 = (unsigned char *)dest;
	s2 = (const unsigned char *)src;
	if (dest == NULL || src == NULL)
		return (dest);
	while (n--)
		*s1++ = *s2++;
	return (dest);
}
