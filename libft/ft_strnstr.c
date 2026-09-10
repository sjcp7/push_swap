/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 12:39:42 by ljanuari          #+#    #+#             */
/*   Updated: 2026/07/31 15:05:05 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	size;
	size_t	i;

	if (!little || !big)
		return (NULL);
	size = ft_strlen(little);
	if (!*little)
		return ((char *)big);
	while (len && *big)
	{
		i = 0;
		while (big[i] == little[i] && i < len && i < size)
			i++;
		if (i == size)
			return ((char *)big);
		len--;
		big++;
	}
	return (NULL);
}
