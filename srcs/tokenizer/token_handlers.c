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

int	handle_edge_pipe(t_token **tokens, t_data *data);

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

int	handle_logical_and(const char *s, int *pos, t_token **tokens)
{
	int		i;
	char	next;

	i = *pos;
	next = 0;
	if (add_token(tokens, s, (t_token_pos){i, 2}, TOKEN_AND))
		return (ENOSPC);
	(*pos) += 2;
	return (0);
}

int	handle_pipes(const char *s, int *pos, t_token **tokens, t_data *data)
{
	int		i;
	char	next;
	int		tmp;

	i = *pos;
	next = 0;
	if (s[i + 1])
		next = s[i + 1];
	if (next && next == '|')
	{
		if (add_token(tokens, s, (t_token_pos){i, 2}, TOKEN_OR))
			return (ENOSPC);
		(*pos) += 2;
		return (0);
	}
	if (!next || next == ' ')
	{
		tmp = 1;
		while (s[tmp + i] == ' ')
			tmp++;
		if (s[tmp + i] == '\0')
		{
			if (add_token(tokens, s, (t_token_pos){i, 1}, TOKEN_PIPE))
				return (1);
			if (validate_prompt(*tokens))
				return (1);
			if (handle_edge_pipe(tokens, data))
				return (1);
			(*pos) += tmp;
			return (0);
		}
		else
		{
			if (add_token(tokens, s, (t_token_pos){i, 1}, TOKEN_PIPE))
				return (ENOSPC);
			(*pos) += tmp - 1;
		}
	}
	else
	{
		if (add_token(tokens, s, (t_token_pos){i, 1}, TOKEN_PIPE))
			return (1);
		(*pos)++;
	}
	return (0);
}

int	handle_io(const char *s, int *pos, t_token **tokens)
{
	int		i;
	char	next;

	i = *pos;
	next = 0;
	if (s[i + 1])
		next = s[i + 1];
	if (next && (s[i] == '<' && next == '<'))
	{
		if (add_token(tokens, s, (t_token_pos){i, 2}, TOKEN_HEREDOC))
			return (ENOSPC);
		(*pos) += 2;
	}
	else if (next && (s[i] == '>' && next == '>'))
	{
		if (add_token(tokens, s, (t_token_pos){i, 2}, TOKEN_APPEND))
			return (ENOSPC);
		(*pos) += 2;
	}
	else if (s[i] == '<')
	{
		if (add_token(tokens, s, (t_token_pos){i, 1}, TOKEN_IN))
			return (ENOSPC);
		(*pos)++;
	}
	else if (s[i] == '>')
	{
		if (add_token(tokens, s, (t_token_pos){i, 1}, TOKEN_OUT))
			return (ENOSPC);
		(*pos)++;
	}
	return (0);
}

/* edge case for pipe as last token */
int	handle_edge_pipe(t_token **tokens, t_data *data)
{
	char	*buf;

	while (1)
	{
		init_signals();
		buf = readline("\033[35m> \033[0m");
		reset_sigquit();
		if (!buf)
		{
			if (errno == 0)
				return (1);
			else
				return (1);
		}
		if (buf && buf[0] == '\0')
		{
			free(buf);
			continue ;
		}
		if (buf)
		{
			if (tokenize_input(buf, tokens, data))
				return (1);
			free(buf);
			return (0);
		}
	}
}
