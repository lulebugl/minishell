/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:39:41 by llebugle          #+#    #+#             */
/*   Updated: 2024/10/25 21:31:14 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dst, int c, size_t count)
{
	size_t			i;
	unsigned char	*d;

	i = -1;
	d = dst;
	while (++i < count)
		*d++ = c;
	return (dst);
}
