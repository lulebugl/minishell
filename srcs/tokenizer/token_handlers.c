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

/* wait for input when last token is a pipe*/
char	*handle_edge_pipe(void)
{
	printf("%sedge pipe not implement yet \n%s", PURPLE, RESET);
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
			display_custom_err(ERR_MSG_QUOTES, ERR_MSG_SYNTAX);
			return (-1);
		}
	}
	token = ft_substr(s, *pos, j - *pos);
	if (!token)
		return (ENOSPC);
	ft_lstadd_back(tokens, ft_lstnew(token));
	*pos = j + 1;
	return (0);
}

int	add_token(t_token **tokens, char *prompt, int start, int len)
{
	char	*token;

	token = ft_substr(prompt, start, len);
	if (!token)
		return (ENOSPC);
	ft_lstadd_back(tokens, ft_lstnew(token));
	return (0);
}

int	handle_io(char *s, int *pos, char type, t_token **tokens)
{
	int		i;
	char	next;
	char	*op;
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
	else if (s[i] == '|')
	{
		(*pos)++;
		if ((!next || next == ' ') && s[i] == '|')
		{
			tmp = 0;
			while (s[tmp + i + 1] == ' ')
				tmp++;
			if (s[tmp + i + 1] == '\0')
			{
				/* not implemented yet */
				handle_edge_pipe();
				(*pos) += tmp;
				// return (0);
			}
			else
			{
				if (add_token(tokens, s, i, 1))
					return (ENOSPC);
				(*pos) += tmp;
			}
		}
		else
		{
			if (add_token(tokens, s, i, 1))
				return (ENOSPC);
			(*pos)++;
		}
	}
	else
	{
		if (add_token(tokens, s, i, 1))
			return (ENOSPC);
		(*pos)++;
	}
	return (0);
}
