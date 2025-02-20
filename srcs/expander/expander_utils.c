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

int is_quote(int c)
{
	return (c == DOUBLE_QUOTE || c == SINGLE_QUOTE);
}

/*
 * Function: expand_tilde
 * ----------------------------
 *	if the token's first character is a tilde ('~') and is the only character or
 *	the next character is '/', replace the tilde with the $HOME variable.
 *	returns 0 if successful or conditions not met, and 1 on error
 */
int	expand_tilde(t_data *data, t_list *arg, bool expand)
{
	char	*value;
	char	*content;
	int		i;
	
	i = 0;
	content = (char *)arg->content;
	if (!expand || !arg || !content || !content[0])
		return (0);
	// if (is_quote(content[i]))
	// 	i++;
	if (content[i] != '~' || (content[i] == '~' && content[i + 1]
			&& content[i + 1] != '/'))
		return (0);
	value = env_get_value(data->env, "HOME");
	if (!value)
	{
		if (errno)
			return (1);
		arg->content = replace_key(content, "", 1, 0);
		if (!content)
			return (1);
		return (0);
	}
	arg->content = replace_key(content, value, 1, 0);
	if (!content)
		return (1);
	return (0);
}

/*
 * Function: remove_quotes
 * ----------------------------
 *	Remove the quotes at the start and end of the "word"
 *	Free the original string
 * 	Return the new string if no error occured, otherwise NULL
 */
char	*remove_quotes(char *str, bool *expand, int *quoted)
{
	char	*trimmed;

	if (!str)
		return (NULL);
	*quoted = 0;
	if (str[0] == '\"')
		*quoted = DOUBLE_QUOTE;
	if ((!*str) || (*str && (*str != '\'' && *str != '\"')))
		return (str);
	if (*str == '\'')
	{
		*expand = false;
		*quoted = SINGLE_QUOTE;
	}
	trimmed = ft_substr(str, 1, ft_strlen(str) - 2);
	if (!trimmed)
		return (NULL);
	free(str);
	return (trimmed);
}

/*
 * Function: replace_key
 * ----------------------------
 *	Replace env variable in str with its value (*replace)
 *	from pos start.
 *  key_len is the len of the replaced var
 *	free the original str and returns a the new string if successful
 *	otherwise returns NULL without freeing the original str
 */
char	*replace_key(char *str, char *replace, int start, int key_len)
{
	char	*expanded;
	char	*first;
	char	*middle;
	char	*end;

	if (!str || key_len < 0 || !replace)
		return (NULL);
	first = ft_substr(str, 0, start - 1);
	if (!first)
		return (NULL);
	middle = ft_strjoin_n_free(first, replace);
	if (!middle)
		return (NULL);
	end = ft_substr(str, start + key_len, ft_strlen(str));
	if (!end)
		return (free(middle), NULL);
	expanded = ft_strjoin_n_free(middle, end);
	if (!expanded)
		return (free(end), NULL);
	free(end);
	free(str);
	return (expanded);
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
