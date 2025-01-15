/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:56:54 by llebugle          #+#    #+#             */
/*   Updated: 2024/10/25 21:30:57 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr_s2;
	unsigned char	*ptr_s1;

	i = -1;
	if (!n)
		return (0);
	ptr_s1 = (unsigned char *)s1;
	ptr_s2 = (unsigned char *)s2;
	while (++i < n)
		if (ptr_s1[i] != ptr_s2[i])
			return (ptr_s1[i] - ptr_s2[i]);
	return (0);
}

// int main(int ac, char **av)
// {
// 	if (ac > 3)
// 	{
// 		printf("%d\n", ft_memcmp(av[1], av[2], atoi(av[3])));
// 		printf("%d\n", memcmp(av[1], av[2], atoi(av[3])));
// 	}
// 	return (0);
// }