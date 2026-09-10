/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 09:15:26 by ljanuari          #+#    #+#             */
/*   Updated: 2026/08/03 09:16:04 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		size;
	char		*sub;

	if (!s)
		return (NULL);
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
