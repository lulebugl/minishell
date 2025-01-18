/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:05:54 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/15 19:05:57 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static inline int is_operator(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	tokenize_input(const char *s, t_token **tokens)
{
	int		i;
	int		tmp;
	int		pos;
	char	*word;

	i = 0;
	tmp = 0;
	while (s[i])
	{
		while (s[i] && s[i] == ' ')
			i++;
		if (!s[i])
			break ;
		if (s[i] == '\'' || s[i] == '\"')
		{
			if (handle_quotes(s, &i, s[i], tokens) != 0)
			{
				if (errno != 0)
					perror(strerror(errno));
				return (1); // SYNTAX_ERR
			}
		}
		else if (s[i] && (s[i] == '<' || s[i] == '>'))
		{
			if (handle_io(s, &i, s[i], tokens) != 0)
				return (1);
		}
		else if (s[i] && s[i] == '|')
		{
			if (handle_pipes(s, &i, tokens) != 0)
				return (1);
		}
		
		/* not handling the env right for now, '$USER' and "$USER" is treated the same */
		else
		{
			pos = i;
			if (!s[i])
				return (0);
			while (s[i] && s[i] != ' ' && !is_operator(s[i]) && s[i] != '\''
				&& s[i] != '\"')
				i++;
			word = ft_substr(s, pos, i - pos);
			ft_lstadd_back(tokens, ft_lstnew(word));
		}
	}
	return (0);
}

