/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 15:11:38 by ljanuari          #+#    #+#             */
/*   Updated: 2026/07/30 15:27:03 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*src;
	unsigned char	w;

	src = (unsigned char *)s;
	w = (unsigned char)c;
	if (s == NULL)
		return (NULL);
	while (n--)
		*src++ = w;
	return (s);
}
