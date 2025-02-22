/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_del_all_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:26:26 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/22 20:26:27 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*str_del_all_char(char *str, int c)
{
	int		len;
	char	*new_str;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	j = 0;
	i = -1;
	while (str[++i])
		if (str[i] == c)
			j++;
	new_str = malloc(sizeof(char) * (len - j + 1));
	if (!new_str)
		return (free(str), NULL);
	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] != c)
			new_str[j++] = str[i];
	new_str[j] = '\0';
	return (new_str);
}
