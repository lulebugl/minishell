/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:39:41 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/24 20:39:43 by llebugle         ###   ########.fr       */
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

int	validate_prompt(t_data *data, t_token *token)
{
	t_token	*curr;

	curr = token;
	if (has_balanced_parentheses(token) == false)
		return (msg_custom_err("unclosed parentheses.\n", "syntax error : "),
			ERR_SYNTAX);
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
		curr = curr->next;
	}
	return (0);
}

