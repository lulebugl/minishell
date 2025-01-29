#include "../../includes/minishell.h"

#define COLOR_RESET "\x1b[0m"
#define COLOR_WORD "\e[0;35m"    // Light blue
#define COLOR_PIPE "\x1b[38;5;213m"    // Pink
#define COLOR_REDIR "\x1b[38;5;220m"   // Yellow
#define COLOR_AND "\e[0;36m"
#define COLOR_OR "\e[0;36m"
#define COLOR_PAR "\e[0;32m"
#define COLOR_SPECIAL "\x1b[38;5;159m" // Cyan

void	print_tokens_formatted(t_token *tokens)
{
	t_token		*current;
	int			token_count;
	const char	*type_str[] = {"WORD", "PIPE", "REDIR_IN", "REDIR_OUT",
			"REDIR_APPEND", "HEREDOC", "AND", "OR", "OPEN_PAR", "CLOSED_PAR"};

	// Type strings with their corresponding colors
	const char *type_colors[] = {
		COLOR_WORD,    // TOKEN_WORD
		COLOR_PIPE,    // TOKEN_PIPE
		COLOR_REDIR,   // TOKEN_REDIR_IN
		COLOR_REDIR,   // TOKEN_REDIR_OUT
		COLOR_REDIR,   // TOKEN_REDIR_APPEND
		COLOR_SPECIAL, // TOKEN_HEREDOC
		COLOR_AND,   // TOKEN_REDIR_APPEND
		COLOR_OR,   // TOKEN_REDIR_APPEND
		COLOR_PAR,    // TOKEN_PARENTHESIS
		COLOR_PAR,    // TOKEN_PARENTHESIS
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

// Helper function to free token list
void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
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
		// printf("err tokenize input : %d\n", err);
		printf(RESET);
		return ;
	}
	printf(RESET);
	print_tokens_formatted(tokens);
	free_tokens(tokens);
}
