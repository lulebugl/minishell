/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:42:56 by llebugle          #+#    #+#             */
/*   Updated: 2024/10/24 14:41:33 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	len;

	src_len = ft_strlen(src);
	if (!dstsize)
		return (src_len);
	if (src_len >= dstsize - 1)
		len = dstsize - 1;
	else
		len = src_len;
	ft_memcpy(dst, src, len);
	*(dst + len) = '\0';
	return (src_len);
}
