/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:58:24 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/18 17:08:55 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* edge case for pipe as last token */
int	handle_edge_pipe(t_token **tokens)
{
	char	*buf;

	while (1)
	{
		buf = readline("> ");
		if (!buf)
		{
			// ctrl-D
			if (errno == 0)
				return (1);
			// ctrl-C
			else
				return (1);
		}
		// empty line
		if (buf && buf[0] == '\0')
		{
			free(buf);
			continue ;
		}
		if (buf)
		{
			if (tokenize_input(buf, tokens))
				return (1);
			free(buf);
			return (0);
		}
	}
}

int	add_token(t_token **tokens, const char *prompt, int start, int len)
{
	char	*token;

	token = ft_substr(prompt, start, len);
	if (!token)
		return (1);
	ft_lstadd_back(tokens, ft_lstnew(token));
	return (0);
}

int	handle_quotes(const char *s, int *pos, char type, t_token **tokens)
{
	char	*token;
	int		j;

	(*pos)++;
	j = *pos;
	while (s[j] && s[j] != type)
	{
		j++;
		if (s[j] == '\0')
		{
			msg_custom_err(ERR_MSG_QUOTES, ERR_MSG_SYNTAX);
			return (1);
		}
	}
	if (add_token(tokens, s, *pos, j - *pos))
		return (ENOSPC);
	*pos = j + 1;
	return (0);
}

int	handle_pipes(const char *s, int *pos, t_token **tokens)
{
	int		i;
	char	next;
	int		tmp;

	i = *pos;
	next = 0;
	if (s[i + 1])
		next = s[i + 1];
	if (!next || next == ' ')
	{
		tmp = 1;
		while (s[tmp + i] == ' ')
			tmp++;
		if (s[tmp + i] == '\0')
		{
			/* not implemented yet */
			if (add_token(tokens, s, i, 1))
				return (ENOSPC);
			if (handle_edge_pipe(tokens))
			{
				perror(strerror(errno));
				return (1);
			}
			(*pos) += tmp;
			return (0);
		}
		else
		{
			if (add_token(tokens, s, i, 1))
				return (ENOSPC);
			(*pos) += tmp - 1;
		}
	}
	else
	{
		if (add_token(tokens, s, i, 1))
			return (1);
		(*pos)++;
	}
	return (0);
}

int	handle_io(const char *s, int *pos, char type, t_token **tokens)
{
	int		i;
	char	next;
	int		tmp;

	i = *pos;
	next = 0;
	if (s[i + 1])
		next = s[i + 1];
	if (next && (s[i] == '>' && next == '>') || (s[i] == '<' && next == '<'))
	{
		if (add_token(tokens, s, i, 2))
			return (ENOSPC);
		(*pos) += 2;
	}
	else
	{
		if (add_token(tokens, s, i, 1))
			return (ENOSPC);
		(*pos)++;
	}
	return (0);
}

