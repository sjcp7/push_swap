/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 10:33:48 by ljanuari          #+#    #+#             */
/*   Updated: 2026/07/31 15:08:31 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	length;

	if (!src || !dst)
		return (0);
	length = ft_strlen(src);
	if (!size)
		return (length);
	while (*src && (size - 1))
	{
		*dst++ = *src++;
		size--;
	}
	*dst = '\0';
	return (length);
}
