/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:13:51 by llebugle          #+#    #+#             */
/*   Updated: 2024/10/26 00:08:54 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	len_little;

	i = 0;
	if (*big == *little && *big == 0)
		return ((char *)big);
	if (*big == 0 && len == 0)
		return (NULL);
	len_little = ft_strlen(little);
	if (len_little == 0)
		return ((char *)big);
	while (big[i] && len - i >= len_little && i < len)
	{
		if (!ft_memcmp(big + i, little, len_little))
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
