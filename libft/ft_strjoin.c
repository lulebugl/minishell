/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:43:47 by llebugle          #+#    #+#             */
/*   Updated: 2024/10/26 14:51:06 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	len;

	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	new = malloc(sizeof(char) * len + 1);
	if (!new)
		return (NULL);
	ft_strlcpy(new, s1, ft_strlen(s1) + 1);
	ft_strlcat(new, s2, len + 1);
	return (new);
}

/*
 * Function: ft_strjoin_n_free
 * ----------------------------
 *	concatenate *s1 and *s2 and free *s1
 *  Returns the allocated new strings if success, otherwise NULL
 */
char	*ft_strjoin_n_free(char *s1, char const *s2)
{
	char	*new;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		len = ft_strlen(s2);
	else
		len = ft_strlen(s1) + ft_strlen(s2);
	new = malloc(sizeof(char) * len + 1);
	if (!new)
		return (free(s1), NULL);
	i = -1;
	while (s1[++i] && i < len)
		new[i] = s1[i];
	j = -1;
	while (s2[++j] && i + j < len)
		new[i + j] = s2[j];
	new[i + j] = '\0';
	if (s1)
		free(s1);
	return (new);
}
