/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:08:31 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/24 17:08:35 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*replace_key(char *str, char *replace, int start, int key_len);

int	handle_exit_status(t_data *data, t_token *token, int *i)
{
	char	*value;
	int		start;

	start = ++(*i);
	value = ft_itoa(data->status);
	if (!value)
		return (1);
	token->content = replace_key(token->content, value, start, 2);
	free(value);
	if (!token->content)
		return (1);
	return (0);
}

static int	handle_env_value(t_token *token, char *value, char *key, int start)
{
	if (!value)
	{
		printf("TEST\n");
		if (errno)
			return (1);
		token->content = replace_key(token->content, "", start, ft_strlen(key));
		if (!token->content)
			return (1);
		return (0);
	}
	token->content = replace_key(token->content, value, start, ft_strlen(key));
	if (!token->content)
		return (1);
	printf("final -> %s\n", key);
	return (0);
}

static int	handle_env_var(t_token *token, t_env *env, int *i)
{
	char	*key;
	char	*value;
	int		start;

	start = ++(*i);
	while ((ft_isalnum((int)token->content[*i]) || token->content[*i] == '_')
		&& token->content[*i] != '\"')
		(*i)++;
	key = ft_strndup(token->content + start, *i - start);
	if (!key)
		return (1);
	// printf("key -> %s\n", key);
	value = env_get_value(env, key);
	if (handle_env_value(token, value, key, start))
		return (1);
	free(key);
	return (0);
}

int	expand_token_recursive(t_data *data, t_token *token, t_env *env,
		bool expand)
{
	int	i;

	i = 0;
	
	while (token->content[i] && token->content[i] != '$')
		i++;
	if (token->content[i] == '$' && token->content[i + 1] && token->content[i
		+ 1] == '?' && expand)
	{
		if (handle_exit_status(data, token, &i))
			return (1);
		return (expand_token_recursive(data, token, env, expand));
	}
	else if (token->content[i + 1] && token->content[i] == '$' && expand)
	{
		if (handle_env_var(token, env, &i))
			return (1);
		return (expand_token_recursive(data, token, env, expand));
	}
	if (token->content[i] && token->content[i + 1] != '\0' && expand)
		return (expand_token_recursive(data, token, env, expand));
	return (0);
}

int	expand_token(t_data *data, t_token *token, t_env *env, bool expand)
{
	int i;
	int start;
	char *key;
	char *value;

	i = 0;
	while (token->content[i] && token->content[i] != '$')
		i++;
	if (token->content[i] == '$' && token->content[i + 1]  && token->content[i
		+ 1] == '?' && expand)
	{
		if (handle_exit_status(data, token, &i))
			return (1);
		return (expand_token(data, token, env, expand));
	}
	else if (token->content[i + 1] && token->content[i] == '$'
		&& expand == true)
	{
		start = ++i;
		while ((ft_isalnum((int)token->content[i]) || token->content[i] == '_')
			&& token->content[i] != '\"')
			i++;
		key = ft_strndup(token->content + start, i - start);
		printf("key -> %s\n", key);
		value = env_get_value(env, key);
		if (!value)
		{
			if (errno)
				return (free(key), 1);
			else
			{
				token->content = replace_key(token->content, "", start,
						ft_strlen(key));
				if (!token->content)
					return (free(key), 1);
				printf("new -> %s\n", token->content);
				free(key);
				return (expand_token(data, token, env, expand));
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
		return (expand_token(data, token, env, expand));
	return (0);
}

