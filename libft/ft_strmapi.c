/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 13:38:03 by ljanuari          #+#    #+#             */
/*   Updated: 2026/08/03 14:10:16 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*mapi;

	if (!s || f == NULL)
		return (NULL);
	len = ft_strlen(s);
	mapi = (char *) malloc((len + 1) * sizeof(char));
	if (!mapi)
		return (NULL);
	mapi[len] = '\0';
	while (len--)
		mapi[len] = f(len, s[len]);
	return (mapi);
}
