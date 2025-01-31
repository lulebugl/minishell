/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:08:31 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/30 22:39:06 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: remove_quotes
 * ----------------------------
 *	Remove the quotes at the start and end of the "word"
 *	Free the original string
 * 	Return the new string if no error occured, otherwise NULL
 */
char	*remove_quotes(char *str, bool *expand)
{
	char	*trimmed;

	if (!str)
		return (NULL);
	if ((!*str) || (*str && (*str != '\'' && *str != '\"')))
		return (str);
	if (*str == '\'')
		*expand = false;
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
	bool	quoted;

	quoted = false;
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

/*
 * Function: expand_tilde
 * ----------------------------
 *	if the token's first character is a tilde ('~') and is the only character or
 *	the next character is '/', replace the tilde with the $HOME variable. 
 *	returns 0 if successful or conditions not met, and 1 on error
 */
int	expand_tilde(t_data *data, t_token *token, bool expand)
{
	char	*value;

	if (!expand || !token || !token->content || !token->content[0])
		return (0);
	if (token->content[0] != '~' || (token->content[0] == '~'
			&& token->content[1] && token->content[1] != '/'))
		return (0);
	value = env_get_value(data->env, "HOME");
	if (!value)
	{
		if (errno)
			return (1);
		token->content = replace_key(token->content, "", 1, 0);
		if (!token->content)
			return (1);
		return (0);
	}
	token->content = replace_key(token->content, value, 1, 0);
	if (!token->content)
		return (1);
	return (0);
}
