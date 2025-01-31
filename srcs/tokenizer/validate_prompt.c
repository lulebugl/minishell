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

// int is_par_closed(t_token *token)
// {
// 	t_token *curr;
	
// 	curr = token->next;
// 	while (curr)
// 	{
// 		if (token->type == TOKEN_CLOSE_PAR)
// 			return (1);
// 		curr = curr->next;
// 	}
// 	return (0);
// }

// int is_par_closed(t_token *start, t_token *end)
// {
// 	t_token *curr;
	
// 	curr = start;
// 	while (curr)
// 	{
// 		if (curr->type == TOKEN_OPEN_PAR)
// 		{
// 			// while curr
// 			return (1);
// 		curr = curr->next;
// 	}
// 	return (0);
// }

int	validate_prompt(t_data *data, t_token *token)
{
	t_token *curr;
	
	curr = token;
	while (curr)
	{
		if (is_redirection(curr->type))
		{
			if (!curr->next)
				return (msg_unexpected_token('\n'), 1);
			if (curr->next->type != TOKEN_WORD)
				return (msg_unexpected_token(curr->next->type), 1);
		}
		if (curr->type == TOKEN_PIPE)
		{
			if (curr->next && curr->next->type == TOKEN_PIPE)
				return (msg_unexpected_token('|'), 1);
		}
		// else if (curr->type == TOKEN_OPEN_PAR)
		// 	if (!is_par_closed(curr))
		// 		return (msg_custom_err("unclosed parenthesis\n", "syntax error :"), 1);
		curr = curr->next;
	}
	return (0);
}
