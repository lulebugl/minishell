/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:39:41 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/20 19:16:19 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_balanced_parentheses(t_token *tokens)
{
	int		count;
	t_token	*curr;

	if (!tokens)
		return (true);
	curr = tokens;
	count = -1;
	while (curr)
	{
		if (curr->type == TOKEN_OPEN_PAR)
			count++;
		else if (curr->type == TOKEN_CLOSE_PAR)
		{
			if (count < 0)
				return (false);
			count--;
		}
		curr = curr->next;
	}
	return (count == -1);
}

bool	has_balanced_quotes(t_token **tokens)
{
	char	*str;
	int		i;
	char	quote;

	while ((*tokens))
	{
		if ((*tokens)->type == TOKEN_WORD)
		{
			str = (*tokens)->content;
			i = -1;
			while (str[++i])
			{
				if (str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTE)
				{
					quote = str[i++];
					while (str[i] && str[i] != quote)
						i++;
					if (!str[i])
						return (false);
				}
			}
		}
		(*tokens) = (*tokens)->next;
	}
	return (true);
}

int	validate_prompt(t_token *token)
{
	t_token	*curr;

	if (!token)
		return (1);
	curr = token;
	if (has_balanced_parentheses(token) == false)
		return (msg_custom_err("unclosed parentheses.\n", "syntax error : "),
			ERR_SYNTAX);
	if (has_balanced_quotes(&token) == false)
		return (msg_custom_err(ERR_MSG_QUOTES, ERR_MSG_SYNTAX), ERR_SYNTAX);
	if (curr && (curr->type == TOKEN_PIPE || curr->type == TOKEN_AND
			|| curr->type == TOKEN_OR))
		return (msg_unexpected_token(curr->content), ERR_SYNTAX);
	while (curr)
	{
		if (check_empty_parenthesis(curr))
			return (ERR_SYNTAX);
		if (check_redirections(curr))
			return (ERR_SYNTAX);
		if (check_others(curr))
			return (ERR_SYNTAX);
		curr = curr->next;
	}
	return (0);
}
