/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:32:42 by llebugle          #+#    #+#             */
/*   Updated: 2024/10/26 14:12:36 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_tab(char **tab, size_t i)
{
	while (i--)
		free(tab[i]);
	free(tab);
}

static size_t	count_words(char const *s, char c)
{
	int		i;
	size_t	size;

	i = 0;
	size = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			while (s[i] && s[i] != c)
				i++;
			size++;
		}
	}
	return (size);
}

static char	**fill_tab(char **tab, char const *s, char c)
{
	size_t	i;
	size_t	start;
	size_t	x;

	i = 0;
	x = 0;
	while (s[x])
	{
		if (s[x] == c)
			x++;
		else
		{
			start = x;
			while (s[x] && s[x] != c)
				x++;
			tab[i] = ft_substr(s, start, x - start);
			if (!tab[i])
				return (free_tab(tab, i), NULL);
			i++;
		}
	}
	tab[i] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = ft_calloc(count_words(s, c) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	return (fill_tab(tab, s, c));
}
