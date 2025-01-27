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

static bool	is_redirection(int type)
{
	return (type == TOKEN_IN || type == TOKEN_OUT || type == TOKEN_APPEND
		|| type == TOKEN_HEREDOC);
}

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
		curr = curr->next;
	}
	return (0);
}
