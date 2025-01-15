/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:47:37 by llebugle          #+#    #+#             */
/*   Updated: 2024/10/26 14:27:22 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ptr_dst;
	unsigned char	*ptr_src;

	i = 0;
	ptr_dst = (unsigned char *)dst;
	ptr_src = (unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		*(ptr_dst + i) = *(ptr_src + i);
		i++;
	}
	return (dst);
}

// int main(int ac, char **av)
// {
// 	if (ac > 3)
// 	{
// 		char *dst = strdup(av[1]);
// 		char *src = strdup(av[2]);
// 		printf("%s\n", (char *)ft_memcpy(dst, src, ft_atoi(av[3])));
// 		printf("%s\n", (char *)memcpy(av[1], av[2], ft_atoi(av[3])));
// 	}
// 	return (0);
// }