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

//need to implement better error handling
int	tokenize_input(const char *s, t_token **tokens, t_data *data)
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
			data->status = handle_quotes(s, &i, s[i], tokens);
			if (data->status != 0)
			{
				if (errno != 0)
					perror(strerror(errno));
				return (1);
			}
		}
		else if (s[i] && (s[i] == '<' || s[i] == '>'))
		{
			data->status = handle_io(s, &i, s[i], tokens); 
			if (data->status != 0)
				return (1);
		}
		else if (s[i] && s[i] == '|')
		{
			data->status = handle_pipes(s, &i, tokens, data); 
			if (data->status != 0)
				return (1);
		}
		else
		{
			pos = i;
			if (!s[i])
				return (0);
			while (s[i] && s[i] != ' ' && !is_operator(s[i]) && s[i] != '\''
				&& s[i] != '\"')
				i++;
			word = ft_substr(s, pos, i - pos);
			if (!word)
				return(1);
			push_token(tokens, new_token(word, TOKEN_WORD));
		}
	}
	return (0);
}

