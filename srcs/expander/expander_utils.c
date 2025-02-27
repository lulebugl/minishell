/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:04:57 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/30 22:42:15 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(int c)
{
	return (c == DOUBLE_QUOTE || c == SINGLE_QUOTE);
}

/*
 * Function: replace_substring
 * ----------------------------
 * Replaces a portion of the original string with a new substring
 * Returns a new allocated string with the replacement done
 */
char	*replace_substring(char *str, size_t start, size_t len, char *replace)
{
	size_t	total_len;
	char	*result;

	if (!str || len < 0 || !replace)
		return (NULL);
	total_len = ft_strlen(str) - len + ft_strlen(replace);
	result = malloc(sizeof(char) * total_len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, str, start);
	ft_strcpy(result + start, replace);
	ft_strcpy(result + start + ft_strlen(replace), str + start + len);
	free((char *)str);
	return (result);
}

/*
 * Function: skip_in_single_quote
 * ----------------------------
 * skip every character inside single quotes
 * and returns true, else return false
 */
bool	skip_in_single_quote(char *str, int *i)
{
	if (!str || str[*i] != SINGLE_QUOTE)
	{
		if (str && str[*i] == DOUBLE_QUOTE)
			(*i)++;
		return (false);
	}
	(*i)++;
	while (str[*i] && str[*i] != SINGLE_QUOTE)
		(*i)++;
	if (str[*i] == SINGLE_QUOTE)
		(*i)++;
	return (true);
}

bool	skip_quoted(char *str, int *i)
{
	if (!str || (str[*i] != SINGLE_QUOTE && str[*i] != DOUBLE_QUOTE))
		return (false);
	if (str[*i] == SINGLE_QUOTE)
	{
		(*i)++;
		while (str[*i] && str[*i] != SINGLE_QUOTE)
			(*i)++;
		if (str[*i] == SINGLE_QUOTE)
			(*i)++;
		return (true);
	}
	else if (str[*i] == DOUBLE_QUOTE)
	{
		(*i)++;
		while (str[*i] && str[*i] != DOUBLE_QUOTE)
			(*i)++;
		if (str[*i] == DOUBLE_QUOTE)
			(*i)++;
		return (true);
	}
	return (true);
}

bool	has_unquoted_space(const char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTE)
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (str[i])
				i++;
		}
		else if (str[i] == ' ')
			return (true);
		else
			i++;
	}
	return (false);
}
