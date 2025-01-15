/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:52:15 by llebugle          #+#    #+#             */
/*   Updated: 2024/10/24 21:19:58 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len_nb(long n)
{
	size_t	len;

	len = 0;
	while (n / 10)
	{
		n /= 10;
		len++;
	}
	return (len + 1);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nb;
	size_t	len;

	if (n < 0)
		nb = -(long)n;
	else
		nb = n;
	len = len_nb(nb);
	if (n < 0)
		len++;
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	len--;
	while (nb >= 10)
	{
		str[len--] = nb % 10 + 48;
		nb /= 10;
	}
	str[len] = nb % 10 + 48;
	return (str);
}
