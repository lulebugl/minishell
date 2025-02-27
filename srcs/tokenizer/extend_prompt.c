/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:17:42 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/24 19:17:54 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_extended(t_token **tokens, t_data *data)
{
	char	*buf;

	while (1)
	{
		signal(SIGINT, signal_ctlc);
		buf = readline("\033[35m> \033[0m");
		if (g_sig == SIGINT)
			return (free(buf), 1);
		if (!buf)
		{
			ft_printf_fd(STDERR_FILENO,
				"minishell: syntax error: unexpected end of file\n");
			return (data_free(data), exit(ERR_SYNTAX), ERR_SYNTAX);
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
			return (free(buf), 0);
		}
	}
}

int	extend_prompt(t_data *data, t_token **tokens, const char *s, int *pos)
{
	int	i;

	if (!s)
		return (1);
	if (!s[*pos])
	{
		if (validate_prompt(*tokens) || read_extended(tokens, data))
			return (1);
	}
	else if (s[*pos] == ' ')
	{
		i = 0;
		while (s[*pos] && s[*pos + i] == ' ')
			i++;
		if (!s[*pos + i])
			if (validate_prompt(*tokens) || read_extended(tokens, data))
				return (1);
		(*pos) += i;
	}
	return (0);
}
