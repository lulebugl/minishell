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

int	find_first_quote(const char *str)
{
	while (*str)
	{
		if (*str == SINGLE_QUOTE || *str == DOUBLE_QUOTE)
			return (*str);
		str++;
	}
	return (0);
}

int	del_empty_args(t_list **head, t_list *node_to_delete)
{
	t_list	**curr;
	t_list	*tmp;

	if (!head || !*head || !node_to_delete)
		return (1);
	curr = head;
	while (*curr && *curr != node_to_delete)
		curr = &(*curr)->next;
	if (*curr && (*curr)->content && ((char *)(*curr)->content)[0] == '\0')
	{
		tmp = *curr;
		*curr = (*curr)->next;
		if (tmp->content)
		{
			free(tmp->content);
			tmp->content = NULL;
		}
		free(tmp);
		tmp = NULL;
		return (1);
	}
	return (0);
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
