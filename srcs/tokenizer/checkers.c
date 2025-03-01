/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:11:32 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/26 20:11:34 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline bool	is_redirection(int type)
{
	return (type == TOKEN_IN || type == TOKEN_OUT || type == TOKEN_APPEND
		|| type == TOKEN_HEREDOC);
}

int	check_empty_parenthesis(t_token *curr)
{
	if (curr->type == TOKEN_OPEN_PAR && curr->next
		&& curr->next->type == TOKEN_CLOSE_PAR)
	{
		if (!curr->next->next)
			return (msg_unexpected_token("\n"), ERR_SYNTAX);
		return (msg_unexpected_token(curr->next->next->content), ERR_SYNTAX);
	}
	return (0);
}

int	check_redirections(t_token *curr)
{
	if (is_redirection(curr->type))
	{
		if (!curr->next)
			return (msg_unexpected_token("\n"), ERR_SYNTAX);
		if (curr->next->type != TOKEN_WORD)
			return (msg_unexpected_token(curr->next->content), ERR_SYNTAX);
	}
	return (0);
}

int	check_others(t_token *curr)
{
	if (curr->type == TOKEN_WORD && curr->next
		&& curr->next->type == TOKEN_OPEN_PAR)
		return (msg_unexpected_token(curr->next->content), ERR_SYNTAX);
	if (curr->type == TOKEN_PIPE)
	{
		// if (curr->next && is_redirection(curr->next->type))
		// 	return (msg_unexpected_token(curr->next->content), ERR_SYNTAX);
		if (curr->next && curr->next->type == TOKEN_PIPE)
			return (msg_unexpected_token(curr->next->content), ERR_SYNTAX);
	}
	if (curr->type == TOKEN_OR || curr->type == TOKEN_AND)
	{
		if (curr->next && (curr->next->type == TOKEN_PIPE
				|| curr->next->type == TOKEN_OR
				|| curr->next->type == TOKEN_AND))
			return (msg_unexpected_token(curr->next->content), ERR_SYNTAX);
	}
	return (0);
}
