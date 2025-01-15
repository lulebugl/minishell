/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:40:30 by llebugle          #+#    #+#             */
/*   Updated: 2024/10/23 13:42:35 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!size)
		return (ft_strlen(src));
	while (dest[i] && i < size)
		i++;
	while (src[j] && i + j < size - 1)
	{
		if (i + j < size)
			dest[i + j] = src[j];
		j++;
	}
	if (i + j < size)
		dest[i + j] = '\0';
	if (size < i)
		return (size + j);
	return (ft_strlen(src) + i);
}
