/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:53:40 by llebugle          #+#    #+#             */
/*   Updated: 2024/10/26 14:28:48 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*ptr_dst;
	char	*ptr_src;

	ptr_dst = (char *)dst;
	ptr_src = (char *)src;
	if (!dst && !src)
		return (NULL);
	if (ptr_dst < ptr_src)
	{
		i = -1;
		while (++i < len)
			ptr_dst[i] = ptr_src[i];
	}
	else
	{
		while (len--)
			ptr_dst[len] = ptr_src[len];
	}
	return (dst);
}
