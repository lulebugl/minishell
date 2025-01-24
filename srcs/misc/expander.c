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
// - [x] handle env var not found (empty replace)
// - [ ]better error management in expand tokens
// - [ ]refactor expander
// - [ ]remember to free everything
// - [x]Handle special Case : [$$], [$?]

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
	// printf("final -> %s\n", expanded);
	return (expanded);
}


int	expand_token(t_data *data, t_token *token, t_env *env, bool expand);
int	expand_token_recursive(t_data *data, t_token *token, t_env *env,
		bool expand);

int	expander(t_data *data)
{
	bool	expand;
	t_token *token;
	
	// shouldn't need it
	// if (!data->env)
	// 	return (0);
	token = data->tokens;
	while (token)
	{
		if (token->content)
		{
			expand = true;
			token->content = remove_quotes(token->content, &expand);
			printf("s : %s\n", token->content);
			if (!token->content)
				return (1);
			if (expand_token_recursive(data, token, data->env, expand))
				return (1);
			
		}
		token = token->next;
	}
	return (0);
}

