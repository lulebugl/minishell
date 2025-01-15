/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:08:10 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/05 11:52:55 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return (write(fd, "(null)", 6));
	else
		return (write(fd, s, ft_strlen(s)));
}
