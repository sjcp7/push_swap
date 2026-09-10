/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanuari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 09:50:31 by ljanuari          #+#    #+#             */
/*   Updated: 2026/08/06 12:01:24 by ljanuari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lines(char const *s, char c)
{
	int	n;

	n = 0;
	if (!s)
		return (0);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			n++;
		while (*s && *s != c)
			s++;
	}
	return (n);
}

static char	*r_strdup(char const *s, char c)
{
	int		len;
	char	*str;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	str = (char *) malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
		str[len] = s[len];
	return (str);
}

static int	verif(char const *s, char ***split, int n)
{
	if (!s || !n)
	{
		*split = (char **) malloc(sizeof(char *) * 1);
		if (!(*split))
			return (-1);
		**split = NULL;
		return (0);
	}
	return (1);
}

static void	*split_abort(char **split, int size)
{
	while (size--)
		free(split[size]);
	free(split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		number_lines;

	number_lines = lines(s, c);
	split = NULL;
	if (verif(s, &split, number_lines) == 0)
		return (split);
	split = (char **) malloc((number_lines + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	split[number_lines] = NULL;
	number_lines = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s == '\0')
			return (split);
		split[number_lines] = r_strdup(s, c);
		if (split[number_lines++] == NULL)
			return (split_abort(split, --number_lines));
		while (*s && *s != c)
			s++;
	}
	return (split);
}
