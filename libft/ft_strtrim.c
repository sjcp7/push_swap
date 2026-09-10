/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 09:17:08 by ljanuari          #+#    #+#             */
/*   Updated: 2026/08/03 11:17:40 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*my_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	size;
	char	*sub;

	while (*s && start--)
		s++;
	size = (len + 1);
	if (ft_strlen(s) < len)
		size = ft_strlen(s) + 1;
	sub = (char *) malloc(size * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (*s && i < len)
		sub[i++] = *s++;
	sub[i] = '\0';
	return (sub);
}

static size_t	verif(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && verif(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && verif(s1[end - 1], set))
		end--;
	return (my_strsub(s1, start, (end - start)));
}
