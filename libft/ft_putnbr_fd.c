/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:27:48 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/05 11:53:43 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	size_t	len;

	nb = n;
	len = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		len++;
		nb = -nb;
	}
	if (nb > 9)
	{
		len += ft_putnbr_fd((nb / 10), fd);
		len += ft_putnbr_fd((nb % 10), fd);
	}
	else
	{
		ft_putchar_fd(nb + 48, fd);
		len++;
	}
	return (len);
}
