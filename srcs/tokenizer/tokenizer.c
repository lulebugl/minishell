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

// Helper function to check if character is an operator
static int	is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

// static int	handle_quotes(const char *s, int start, char type, t_token **tokens)
// {
// 	char	*content;
// 	int		j;
	
// 	start++;
// 	j = start;
// 	while (s[j] && s[j] != type)
// 	{
// 		j++;
// 		if (s[j] == '\0')
// 		{
// 			printf("no end quotes found\n");
// 			return (-1);
// 		}
// 	}
// 	content = ft_substr(s, start, j - start);
// 	ft_lstadd_back(tokens, ft_lstnew(content));
// 	return (j - start + 1);
// }

static int handle_quotes(const char *s, int *start, char type, t_token **tokens)
{
    char    *token;
    int     j;
    
    (*start)++;  // Move past opening quote
    j = *start;
    while (s[j] && s[j] != type)
    {
        j++;
        if (s[j] == '\0')
        {
            printf("no end quotes found\n");
            return (-1);
        }
    }
    token = ft_substr(s, *start, j - *start);
    ft_lstadd_back(tokens, ft_lstnew(token));
    *start = j + 1;  // Update start to position after closing quote
    return (0);
}

int	tokenize_input(const char *s, t_token **tokens)
{
	int i;
	int tmp;
	int start;

	i = 0;
	tmp = 0;
	while (s[i])
	{
		while (s[i] && s[i] == ' ')
			i++;
		if (!s[i])
			break ;
		start = i;
		if (s[i] == '\'' || s[i] == '\"')
		{
			if (handle_quotes(s, &i, s[i], tokens) != 0)
				return (1); //SYNTAX_ERR
		}
		// else if (is_operator(s[i]))
		// {
		// 	// Handle operators (<, >, |, >>, <<)
		// 	if ((s[i] == '>' && s[i + 1] == '>') || (s[i] == '<' && s[i
		// 			+ 1] == '<'))
		// 	{
		// 		char *op = ft_substr(s, i, 2);
		// 		ft_lstadd_back(tokens, ft_lstnew(op));
		// 		i += 2;
		// 	}
		// 	else
		// 	{
		// 		char *op = ft_substr(s, i, 1);
		// 		ft_lstadd_back(tokens, ft_lstnew(op));
		// 		i++;
		// 	}
		// }
		else
		{
			// Handle regular words and environment variables
			while (s[i] && s[i] != ' ' && !is_operator(s[i]) && s[i] != '\''
				&& s[i] != '\"')
				i++;
			char *word = ft_substr(s, start, i - start);
			ft_lstadd_back(tokens, ft_lstnew(word));
		}
	}
	return (0);
}
