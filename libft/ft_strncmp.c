/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 12:09:06 by ljanuari          #+#    #+#             */
/*   Updated: 2026/08/04 11:14:51 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!n || !s1 || !s2)
		return (0);
	while (n-- && *s1 && *s2)
	{
		if (n && *s1 == *s2)
		{
			s1++;
			s2++;
		}
		else
			break ;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
