/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_del_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:26:15 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/22 20:26:18 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*str_del_char(char *str, const char *char_to_del)
{
	int		len;
	char	*new_str;
	int		i;
	int		j;

	if (!str || !char_to_del || char_to_del < str)
		return (NULL);
	len = ft_strlen(str);
	if (char_to_del >= str + len)
		return (free(str), NULL);
	new_str = malloc(len);
	if (!new_str)
		return (free(str), NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (&str[i] != char_to_del)
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}
