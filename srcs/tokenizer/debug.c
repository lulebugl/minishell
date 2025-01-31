/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:48:11 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/29 19:48:12 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "minishell.h"

void	print_tokens_formatted(t_token *tokens)
{
	t_token		*current;
	int			token_count;
	const char	*type_str[] = {"WORD", "PIPE", "REDIR_IN", "REDIR_OUT",
			"REDIR_APPEND", "HEREDOC", "AND", "OR", "OPEN_PAR", "CLOSED_PAR"};

	const char *type_colors[] = {
		COLOR_WORD,
		COLOR_PIPE,
		COLOR_REDIR,
		COLOR_REDIR,
		COLOR_REDIR,
		COLOR_SPECIAL,
		COLOR_AND,
		COLOR_OR,
		COLOR_PAR,
		COLOR_PAR,
	};
	current = tokens;
	token_count = 0;
	printf("=== Token List ===\n");
	if (!current)
	{
		printf("No tokens found.\n");
		printf("================\n");
		return ;
	}
	while (current)
	{
		printf("Token[%d]: Type: %s%-12s%s Value: '%s%s%s'\n", token_count,
			type_colors[current->type], type_str[current->type], RESET,
			type_colors[current->type], (char *)current->content, RESET);
		current = current->next;
		token_count++;
	}
	printf("================\n");
}

void	test_arg_input(const char *input, t_data *data)
{
	t_token	*tokens;
	int		err;

	tokens = NULL;
	printf(PURPLE);
	err = tokenize_input(input, &tokens, data);
	if (err)
	{
		printf(RESET);
		return ;
	}
	printf(RESET);
	print_tokens_formatted(tokens);
	clear_tokens(&tokens);
}

