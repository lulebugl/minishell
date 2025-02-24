/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:58:24 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/20 20:14:52 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_quotes(const char *s, int *start, char type, t_token **tokens)
{
	int			len;

	len = ++(*start);
	if (!s[len])
		return (msg_custom_err(ERR_MSG_QUOTES, ERR_MSG_SYNTAX), 1);
	while (s[len] && s[len] != type)
		len++;
	if (!s[len])
		return (msg_custom_err(ERR_MSG_QUOTES, ERR_MSG_SYNTAX), 1);
	if (add_token(tokens, s, (t_token_pos){((*start) - 1), (len - (*start)
				+ 2)}, TOKEN_WORD))
		return (ENOSPC);
	*start = len + 1;
	return (0);
}

int	handle_parenthesis(const char *s, int *pos, t_token **tokens)
{
	int		i;
	char	next;

	i = *pos;
	next = 0;
	if (s[i] == '(')
	{
		if (add_token(tokens, s, (t_token_pos){i, 1}, TOKEN_OPEN_PAR))
			return (ENOSPC);
	}
	else if (s[i] == ')')
	{
		if (add_token(tokens, s, (t_token_pos){i, 1}, TOKEN_CLOSE_PAR))
			return (ENOSPC);
	}
	(*pos)++;
	return (0);
}

int	handle_logical_and(t_data *data, const char *s, int *pos, t_token **tokens)
{
	int		i;
	char	next;

	i = *pos;
	next = 0;
	if (add_token(tokens, s, (t_token_pos){i, 2}, TOKEN_AND))
		return (ENOSPC);
	(*pos) += 2;
	return (extend_prompt(data, tokens, s, pos));
}

int	handle_pipes(const char *s, int *pos, t_token **tokens, t_data *data)
{
	int		i;
	char	next;

	i = *pos;
	next = 0;
	if (s[i + 1])
		next = s[i + 1];
	if (next && next == '|')
	{
		if (add_token(tokens, s, (t_token_pos){i, 2}, TOKEN_OR))
			return (ENOSPC);
		(*pos) += 2;
		return (extend_prompt(data, tokens, s, pos));
	}
	else
	{
		if (add_token(tokens, s, (t_token_pos){i, 1}, TOKEN_PIPE))
			return (1);
		(*pos)++;
		return (extend_prompt(data, tokens, s, pos));
	}
	return (0);
}

int	handle_io(const char *s, int *pos, t_token **tokens)
{
	char	next;

	next = 0;
	if (s[*pos + 1])
		next = s[*pos + 1];
	if (next && (s[*pos] == '<' && next == '<'))
	{
		if (add_token(tokens, s, (t_token_pos){*pos, 2}, TOKEN_HEREDOC))
			return (ERROR);
		(*pos) += 2;
	}
	if (next && (s[*pos] == '>' && next == '>'))
	{
		if (add_token(tokens, s, (t_token_pos){*pos, 2}, TOKEN_APPEND))
			return (ERROR);
		(*pos) += 2;
	}
	if (s[*pos] == '<')
		if (add_token(tokens, s, (t_token_pos){(*pos)++, 1}, TOKEN_IN))
			return (ERROR);
	if (s[*pos] == '>')
		if (add_token(tokens, s, (t_token_pos){(*pos)++, 1}, TOKEN_OUT))
			return (ERROR);
	return (0);
}

