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
static char	*remove_quotes(char *str)
{
	char	*trimmed;

	trimmed = ft_substr(str, 1, ft_strlen(str) - 2);
	if (!trimmed)
		return (NULL);
	free(str);
	return (trimmed);
}

/*
 * Function: expand_token
 * ----------------------------
 *	NO DESCRIPTION YET
 */
char	*expand_token(char *str, char *replace, int start, char *tmp)
{
	char	*expanded;
	char	*first;
	char	*middle;
	bool	quoted;
	char	*end;

	quoted = false;
	if (!str)
		return (0);
	first = ft_substr(str, 0, start - 1);
	if (!first)
		return (NULL);
	middle = ft_strjoin(first, replace);
	// protect
	end = ft_substr(str, start + ft_strlen(tmp), ft_strlen(str));
	printf(GREEN);
	printf("end -> %s\n", end);
	printf(RESET);
	expanded = ft_strjoin(middle, end);
	// protect
	free(first);
	free(middle);
	free(str);
	printf("final -> %s\n", expanded);
	return (expanded);
}

int	expander(t_data *data)
{
	t_env	*env;
	bool	expand;
	int		i;
	t_token	*tokens;
	int		start;
	char	*res;
	char	*tmp;
	char	*value;
	int		new_len;

	tokens = data->tokens;
	env = data->env;
	if (!env)
		return (0);
	while (tokens)
	{
		if (tokens->content)
		{
			i = 0;
			// printf("Token -> %s\n", tokens->content);
			expand = true;
			if (tokens->content[i] == '\'')
			{
				expand = false;
				tokens->content = remove_quotes(tokens->content);
				if (!tokens->content)
					return (1);
			}
			else if (tokens->content[i] == '\"')
			{
				tokens->content = remove_quotes(tokens->content);
				if (!tokens->content)
					return (1);
			}
			while (tokens->content[i] && tokens->content[i] != '$')
				i++;
			if (tokens->content[i + 1] && tokens->content[i] == '$'
				&& expand == true)
			{
				start = ++i;
				while ((ft_isalnum((int)tokens->content[i])
						|| tokens->content[i] == '_')
					&& tokens->content[i] != '\"')
					i++;
				tmp = ft_strndup(tokens->content + start, i - start);
				printf("key -> %s\n", tmp);
				value = env_get_value(env, tmp);
				if (!value)
				{
					// i need to replace the content with an empty string instead of the var
					// not quit..
					free(tmp);
					break ;
				}
				printf("value -> %s\n", value);
				new_len = ft_strlen(tokens->content) - ft_strlen(tmp)
					+ ft_strlen(value);
				tokens->content = expand_token(tokens->content, value, start,
						tmp);
				free(tmp);
				// printf("new -> %s\n", tokens->content);
			}
			else
				i++;
		}
		tokens = tokens->next;
	}
	return (0);
}
