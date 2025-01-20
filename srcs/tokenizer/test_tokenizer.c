/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:16:57 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/16 19:17:02 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/tokenizer.h"
#include <stdio.h>
#include <string.h>

// Helper function to print tokens in a clear format
#define COLOR_RESET "\x1b[0m"
#define COLOR_WORD "\x1b[38;5;87m"     // Light blue
#define COLOR_PIPE "\x1b[38;5;213m"    // Pink
#define COLOR_REDIR "\x1b[38;5;220m"   // Yellow
#define COLOR_SPECIAL "\x1b[38;5;159m" // Cyan

static int					launch_program(t_data *data);

void	print_tokens_formatted(t_token *tokens)
{
	t_token		*current;
	int			token_count;
	const char	*type_str[] = {"WORD", "PIPE", "REDIR_IN", "REDIR_OUT",
			"REDIR_APPEND", "HEREDOC"};

	// Type strings with their corresponding colors
	const char *type_colors[] = {
		COLOR_WORD,    // TOKEN_WORD
		COLOR_PIPE,    // TOKEN_PIPE
		COLOR_REDIR,   // TOKEN_REDIR_IN
		COLOR_REDIR,   // TOKEN_REDIR_OUT
		COLOR_REDIR,   // TOKEN_REDIR_APPEND
		COLOR_SPECIAL, // TOKEN_HEREDOC
	};
	current = tokens;
	token_count = 0;
	printf("\n=== Token List ===\n");
	if (!current)
	{
		printf("No tokens found.\n");
		printf("================\n");
		return ;
	}
	while (current)
	{
		printf("Token[%d]: Type: %s%-12s%s Value: '%s%s%s'\n", token_count,
			type_colors[current->type], type_str[current->type], COLOR_RESET,
			type_colors[current->type], (char *)current->content, COLOR_RESET);
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

static int	exec_prompt(const char *prompt, t_data *data)
{
	if (ft_strncmp(prompt, "exit", 5) == 0)
		exit(0);
	test_arg_input(prompt, data);
	return (0);
}

static int	launch_program(t_data *data)
{
	char	*rl;

	while (true)
	{
		rl = readline(PROMPT);
		if (!rl)
			exit(1);
		exec_prompt(rl, data);
	}
	return (0);
}

typedef struct s_test_case
{
	const char				*input;
	const char				*description;
	t_token_type			expected_types[10];
	const char				*expected_values[10];
	int						expected_token_count;
}							t_test_case;

static const t_test_case	test_cases[] = {
	// Basic cases (keep existing ones)
	{"ls -la", "Basic command with flag", {TOKEN_WORD, TOKEN_WORD}, {"ls",
		"-la"}, 2},

	// Empty or whitespace inputs
	{"", "Empty input", {}, {}, 0},
	{"   ", "Only spaces", {}, {}, 0},
	{"\t   \t", "Tabs and spaces", {}, {}, 0},

	// Quote edge cases
	{"echo \"\"", "Empty double quotes", {TOKEN_WORD, TOKEN_WORD}, {"echo",
		"\"\""}, 2},
	{"echo ''", "Empty single quotes", {TOKEN_WORD, TOKEN_WORD}, {"echo", "''"},
		2},
	{"echo \"'\"", "Double quoted single quote", {TOKEN_WORD, TOKEN_WORD},
		{"echo", "\"'\""}, 2},
	{"echo '\"'", "Single quoted double quote", {TOKEN_WORD, TOKEN_WORD},
		{"echo", "'\"'"}, 2},

	// Redirection edge cases
	{">>>>", "Multiple consecutive redirects", {TOKEN_APPEND, TOKEN_APPEND},
		{">>", ">>"}, 2},
	{">", "Single redirect without target", {TOKEN_OUT}, {">"}, 1},
	{"< < < <", "Multiple input redirects with spaces", {TOKEN_IN, TOKEN_IN,
		TOKEN_IN, TOKEN_IN}, {"<", "<", "<", "<"}, 4},
	{"ls > > file", "Double redirect with spaces", {TOKEN_WORD, TOKEN_OUT,
		TOKEN_OUT, TOKEN_WORD}, {"ls", ">", ">", "file"}, 4},

	// Pipe edge cases
	{"||||", "Multiple consecutive pipes", {TOKEN_PIPE, TOKEN_PIPE, TOKEN_PIPE,
		TOKEN_PIPE}, {"|", "|", "|", "|"}, 4},
	{"ls | | | grep", "Multiple pipes with spaces", {TOKEN_WORD, TOKEN_PIPE,
		TOKEN_PIPE, TOKEN_PIPE, TOKEN_WORD}, {"ls", "|", "|", "|", "grep"}, 5},

	// Mixed complex cases
	{"echo \"hello > world\" > file",
		"Redirect in quotes followed by actual redirect", {TOKEN_WORD,
		TOKEN_WORD, TOKEN_OUT, TOKEN_WORD}, {"echo", "\"hello > world\"", ">",
		"file"}, 4},
	{"cat << \"EOF\" | grep 'pattern'",
		"Heredoc with quoted delimiter and pipe", {TOKEN_WORD, TOKEN_HEREDOC,
		TOKEN_WORD, TOKEN_PIPE, TOKEN_WORD}, {"cat", "<<", "\"EOF\"", "|",
		"'pattern'"}, 5},
	{"<< EOF > outfile", "Heredoc with output redirect", {TOKEN_HEREDOC,
		TOKEN_WORD, TOKEN_OUT, TOKEN_WORD}, {"<<", "EOF", ">", "outfile"}, 4},

	// Special characters and edge cases
	{"echo $?", "Exit status variable", {TOKEN_WORD, TOKEN_WORD}, {"echo",
		"$?"}, 2},
	{"echo \\\"hello\\\"", "Escaped quotes", {TOKEN_WORD, TOKEN_WORD}, {"echo",
		"\\\"hello\\\""}, 2},
	{"ls '-la'\"pwd\"", "Connected quoted strings", {TOKEN_WORD, TOKEN_WORD},
		{"ls", "'-la'\"pwd\""}, 2},

	// Terminator case
	{NULL, NULL, {0}, {0}, 0}};

static void	validate_test_case(t_token *tokens, const t_test_case *test)
{
	t_token	*current;
	int		count;
	bool	failed;
	int		token_count;
	t_token	*tmp;
	bool	type_match;
	bool	value_match;

	current = tokens;
	count = 0;
	failed = false;
	printf("\nTesting: %s\nInput: \"%s\"\n", test->description, test->input);
	// Check token count first
	token_count = 0;
	tmp = tokens;
	while (tmp)
	{
		token_count++;
		tmp = tmp->next;
	}
	if (token_count != test->expected_token_count)
	{
		printf("❌ Failed: Expected %d tokens, got %d\n",
			test->expected_token_count, token_count);
		return ;
	}
	// Validate each token
	while (current && count < test->expected_token_count)
	{
		type_match = (current->type == test->expected_types[count]);
		value_match = (strcmp(current->content,
					test->expected_values[count]) == 0);
		if (!type_match || !value_match)
		{
			printf("❌ Token[%d] mismatch:\n", count);
			if (!type_match)
				printf("  Type: Expected %d, got %d\n",
					test->expected_types[count], current->type);
			if (!value_match)
				printf("  Value: Expected \"%s\", got \"%s\"\n",
					test->expected_values[count], (char *)current->content);
			failed = true;
		}
		current = current->next;
		count++;
	}
	if (!failed)
		printf("✅ Test passed successfully\n");
	// Print actual tokens for reference
	print_tokens_formatted(tokens);
	printf("----------------------\n");
}

static void	run_test_suite(t_token **tokens, t_data *data)
{
	int	total_tests;
	int	passed_tests;

	total_tests = 0;
	passed_tests = 0;
	printf("\n=== Starting Tokenizer Test Suite ===\n");
	for (int i = 0; test_cases[i].input != NULL; i++)
	{
		// Clear previous tokens
		// clear_tokens(tokens);
		*tokens = NULL;
		// Process test case
		if (tokenize_input(test_cases[i].input, tokens, data))
		{
			printf("❌ Test %d failed: Could not tokenize input\n", i + 1);
			continue ;
		}
		// Validate results
		validate_test_case(*tokens, &test_cases[i]);
		total_tests++;
	}
	printf("\n=== Test Suite Complete ===\n");
	printf("Total tests: %d\n", total_tests);
}

int	main(int argc, char **argv, char **envp)
{
	t_data data;
	t_token *tokens;

	ft_memset(&data, 0, sizeof(t_data));
	if (argc > 1)
	{
		if (ft_strncmp(argv[1], "auto", 4))
			run_test_suite(&tokens, &data);
	}
	else
		launch_program(&data);

	return (0);
}