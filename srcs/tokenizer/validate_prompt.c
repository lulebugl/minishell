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

static inline bool	is_redirection(int type)
{
	return (type == TOKEN_IN || type == TOKEN_OUT || type == TOKEN_APPEND
		|| type == TOKEN_HEREDOC);
}

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

bool    has_balanced_quotes(t_token *tokens)
{
    t_token *curr;
    char    *str;
    int     i;
    char    quote;

    curr = tokens;
    while (curr)
    {
        if (curr->type == TOKEN_WORD)
        {
            str = curr->content;
            i = 0;
            while (str[i])
            {
                if (str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTE)
                {
                    quote = str[i++];
                    while (str[i] && str[i] != quote)
                        i++;
                    if (!str[i])
                        return (false);
                }
                i++;
            }
        }
        curr = curr->next;
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
	if (has_balanced_quotes(token) == false)
		return (msg_custom_err(ERR_MSG_QUOTES, ERR_MSG_SYNTAX), 1);
	if (curr && (curr->type == TOKEN_PIPE || curr->type == TOKEN_AND
			|| curr->type == TOKEN_OR))
		return (msg_unexpected_token(curr->content), ERR_SYNTAX);
	while (curr)
	{
		if (curr->type == TOKEN_OPEN_PAR && curr->next
			&& curr->next->type == TOKEN_CLOSE_PAR)
		{
			if (!curr->next->next)
				return (msg_unexpected_token("\n"), ERR_SYNTAX);
			return (msg_unexpected_token(curr->next->next->content),
				ERR_SYNTAX);
		}
		if (curr->type == TOKEN_WORD && curr->next
			&& curr->next->type == TOKEN_OPEN_PAR)
		{
			return (msg_unexpected_token(curr->next->content), ERR_SYNTAX);
		}
		if (is_redirection(curr->type))
		{
			if (!curr->next)
				return (msg_unexpected_token("\n"), ERR_SYNTAX);
			if (curr->next->type != TOKEN_WORD)
				return (msg_unexpected_token(curr->next->content), ERR_SYNTAX);
		}
		if (curr->type == TOKEN_PIPE)
		{
			if (curr->next && is_redirection(curr->next->type))
				return (msg_unexpected_token(curr->next->content), ERR_SYNTAX);
			if (curr->next && curr->next->type == TOKEN_PIPE)
				return (msg_unexpected_token(curr->next->content), ERR_SYNTAX);
		}
		if (curr->type == TOKEN_OR || curr->type == TOKEN_AND)
		{
			if (curr->next && (curr->next->type == TOKEN_PIPE || curr->next->type == TOKEN_OR || curr->next->type == TOKEN_AND))
				return (msg_unexpected_token(curr->next->content), ERR_SYNTAX);
		}
		curr = curr->next;
	}
	return (0);
}

