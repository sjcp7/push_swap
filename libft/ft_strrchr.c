/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 11:50:45 by ljanuari          #+#    #+#             */
/*   Updated: 2026/07/31 15:33:25 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int					size;
	unsigned char		a;

	a = (unsigned char)c;
	size = 0;
	if (!s)
		return (NULL);
	while (s[size])
		size++;
	while (size >= 0)
	{
		if (s[size] == a)
			return ((char *)&s[size]);
		size--;
	}
	return (NULL);
}
