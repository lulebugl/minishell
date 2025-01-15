/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:42:46 by llebugle          #+#    #+#             */
/*   Updated: 2024/10/26 14:19:15 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;

	last = NULL;
	if ((char)c)
	{
		while (*s)
		{
			if (*s == (char)c)
				last = (char *)s;
			s++;
		}
	}
	else
		last = ft_strchr(s, c);
	return (last);
}
