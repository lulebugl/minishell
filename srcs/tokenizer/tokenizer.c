/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:05:54 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/20 19:16:22 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	is_operator(char c)
{
	return (c == '>' || c == '<' || c == '|' || c == '(' || c == ')');
}

static int	is_logical_and(const char *s)
{
	if (!(s + 1))
		return (0);
	return (*s == '&' && *(s + 1) == '&');
}

int	handle_word(const char *s, int *pos, t_token **tokens)
{
	int	start;

	start = *pos;
	if (!s || !s[*pos])
		return (0);
	while (s[*pos] && s[*pos] != ' ' && !is_operator(s[*pos])
		&& !is_logical_and(s + *pos))
	{
		if (s[*pos] == SINGLE_QUOTE)
		{
			(*pos)++;
		while (s[(*pos)] && s[*pos] != SINGLE_QUOTE)
				(*pos)++;
		}
		else if (s[(*pos)] == DOUBLE_QUOTE)
		{
			(*pos)++;
			while (s[*pos] && s[*pos] != DOUBLE_QUOTE)
				(*pos)++;
		}
		else
			(*pos)++;
	}
	return (add_token(tokens, s, (t_token_pos){start, *pos - start}, TOKEN_WORD));
}

/*
 *	Creates a linked list **tokens of every token encountered
 *	in *s.
 *	Return 0 on success, otherwise set data->status to last error status.
 */
int	tokenize_input(const char *s, t_token **tokens, t_data *data)
{
	int	i;

	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == ' ')
			i++;
		if (!s[i])
			break ;
		else if (s[i] && (s[i] == '<' || s[i] == '>'))
			data->status = handle_io(s, &i, tokens);
		else if (s[i] && (s[i] == '(' || s[i] == ')'))
			data->status = handle_parenthesis(s, &i, tokens);
		else if (s[i] && s[i + 1] && (s[i] == '&') && (s[i + 1] == '&'))
			data->status = handle_logical_and(data, s, &i, tokens);
		else if (s[i] && s[i] == '|')
			data->status = handle_pipes(s, &i, tokens, data);
		else
			data->status = handle_word(s, &i, tokens);
		if (data->status != 0 && errno != 0)
			return (data->status = errno, perror(strerror(errno)), 1);
		else if (data->status != 0)
			return (1);
	}
	return (0);
}
