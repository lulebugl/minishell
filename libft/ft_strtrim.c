/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:04:28 by llebugle          #+#    #+#             */
/*   Updated: 2024/10/24 17:26:06 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_sep(char const c, char const *charset)
{
	int	i;

	i = -1;
	while (charset[++i] && c)
		if (charset[i] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	size_t	start;
	size_t	end;

	start = 0;
	end = ft_strlen(s1) - 1;
	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	while (is_sep(s1[start], set))
		start++;
	while (is_sep(s1[end], set))
		end--;
	new = ft_substr(s1, start, end - start + 1);
	if (!new)
		return (NULL);
	return (new);
}
