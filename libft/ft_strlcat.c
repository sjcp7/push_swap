/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 11:08:46 by ljanuari          #+#    #+#             */
/*   Updated: 2026/08/04 13:09:19 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	dest_strlen(char const *dest, size_t buff)
{
	size_t	n;

	n = 0;
	while (buff-- && *dest++)
		n++;
	return (n);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	length;

	if (!src || !dst)
		return (0);
	length = ft_strlen(src) + dest_strlen(dst, size);
	if (!size)
		return (length);
	while (size > 0 && *dst)
	{
		dst++;
		size--;
	}
	if (size == 0)
		return (length);
	while ((size > 1) && *src)
	{
		*dst++ = *src++;
		size--;
	}
	*dst = '\0';
	return (length);
}
