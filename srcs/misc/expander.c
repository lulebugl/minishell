/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:04:57 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/22 17:04:59 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TO DO :
// - handle env var not found (empty replace)
// - better error management in expand tokens
// - refactor expander
// - remember to free everything
// - Handle special Case : [$$], [$?]

/*
 * Function: remove_quotes
 * ----------------------------
 *	Remove the quotes at the start and end of the "word"
 *	Free the original string
 * 	Return the new string if no error occured, otherwise NULL
 */
static char	*remove_quotes(char *str, bool *expand)
{
	char	*trimmed;

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
	bool	quoted;
	char	*end;

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
	// printf(GREEN);
	// printf("end -> %s\n", end);
	// printf(RESET);
	expanded = ft_strjoin_n_free(middle, end);
	if (!expanded)
		return (free(end), NULL);
	free(end);
	free(str);
	printf("final -> %s\n", expanded);
	return (expanded);
}

int		expand_token(t_token *token, t_env *env, bool expand)
{
	int i;
	int start;
	char *key;
	char *value;
	
	i = 0;
	while (token->content[i] && token->content[i] != '$')
		i++;
	if (token->content[i + 1] && token->content[i] == '$'
		&& expand == true)
	{
		start = ++i;
		while ((ft_isalnum((int)token->content[i])
				|| token->content[i] == '_')
			&& token->content[i] != '\"')
			i++;
		key = ft_strndup(token->content + start, i - start);
		printf("key -> %s\n", key);
		value = env_get_value(env, key);
		if (!value)
		{
			// i need to replace the content with an empty string instead of the var
			// not quit..
			if (errno)
				return (free(key), 1);
			else
			{
				token->content = replace_key(token->content, "",
						start, ft_strlen(key));
				if (!token->content)
					return (free(key), 1);
				printf("new -> %s\n", token->content);
				free(key);
				return (expand_token(token, env, expand));
			}
		}
		token->content = replace_key(token->content, value, start,
				ft_strlen(key));
		if (!token->content)
			return (free(key), 1);
		free(key);
		// printf("new -> %s\n", tokens->content);
	}
	if (token->content[i] && token->content[i + 1] != '\0')
		return (expand_token(token, env, expand));
	return (0);
}

int	expander(t_data *data, t_token *tokens)
{
	bool	expand;

	// shouldn't need it
	// if (!data->env)
	// 	return (0);
	while (tokens)
	{
		if (tokens->content)
		{
			expand = true;
			tokens->content = remove_quotes(tokens->content, &expand);
			if (!tokens->content)
				return (1);
			if (expand_token(tokens, data->env, expand))
				return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}

