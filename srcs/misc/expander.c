/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:04:57 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/17 12:17:08 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*replace_key(char *str, char *replace, int start, int key_len);
char		*remove_quotes(char *str, bool *expand);

static int	handle_exit_status(t_data *data, t_token *token, int *i)
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
	value = env_get_value(env, key);
	if (handle_env_value(token, value, key, start))
		return (free(key), 1);
	free(key);
	return (0);
}

int	expand_token_recursive(t_data *data, t_token *token, bool expand)
{
	int	i;

	i = 0;
	if (!token)
		return (1);
	while (token->content[i] && token->content[i] != '$')
		i++;
	if (token->content[i] == '$' && token->content[i + 1] && token->content[i
			+ 1] == '?' && expand)
	{
		if (handle_exit_status(data, token, &i))
			return (1);
		return (expand_token_recursive(data, token, expand));
	}
	else if (token->content[i] && token->content[i + 1]
		&& token->content[i] == '$' && expand)
	{
		if (handle_env_var(token, data->env, &i))
			return (1);
		return (expand_token_recursive(data, token, expand));
	}
	if (token->content[i] && token->content[i + 1] != '\0' && expand)
		return (expand_token_recursive(data, token, expand));
	return (0);
}

int	expander(t_data *data)
{
	bool	expand;
	t_token	*token;

	token = data->tokens;
	while (token)
	{
		if (token->content)
		{
			expand = true;
			token->content = remove_quotes(token->content, &expand);
			if (!token->content)
				return (1);
			if (expand_token_recursive(data, token, expand))
				return (1);
			if (expand_tilde(data, token, expand))
				return (1);
		}
		token = token->next;
	}
	return (0);
}
