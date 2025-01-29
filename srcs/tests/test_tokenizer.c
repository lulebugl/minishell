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

#include "minishell.h"

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
	t_token_type			expected_types[20];
	const char				*expected_values[20];
	int						expected_token_count;
}							t_test_case;

static const t_test_case test_cases[] = {
    // Keep your existing basic cases...

    // Parentheses edge cases
    {"(ls)", "Simple parentheses", 
        {TOKEN_OPEN_PAR, TOKEN_WORD, TOKEN_CLOSE_PAR}, 
        {"(", "ls", ")"}, 3},
    
    {"( ls )", "Parentheses with spaces", 
        {TOKEN_OPEN_PAR, TOKEN_WORD, TOKEN_CLOSE_PAR}, 
        {"(", "ls", ")"}, 3},
    
    {"((echo test))", "Nested parentheses", 
        {TOKEN_OPEN_PAR, TOKEN_OPEN_PAR, TOKEN_WORD, TOKEN_WORD, TOKEN_CLOSE_PAR, TOKEN_CLOSE_PAR}, 
        {"(", "(", "echo", "test", ")", ")"}, 6},
    
    // Logical AND edge cases
    {"ls && pwd", "Simple logical AND", 
        {TOKEN_WORD, TOKEN_AND, TOKEN_WORD}, 
        {"ls", "&&", "pwd"}, 3},
    
    {"ls&&pwd", "Logical AND without spaces", 
        {TOKEN_WORD, TOKEN_AND, TOKEN_WORD}, 
        {"ls", "&&", "pwd"}, 3},
    
    {"ls && pwd && echo test", "Multiple logical AND", 
        {TOKEN_WORD, TOKEN_AND, TOKEN_WORD, TOKEN_AND, TOKEN_WORD, TOKEN_WORD}, 
        {"ls", "&&", "pwd", "&&", "echo", "test"}, 6},

    // Complex combinations with parentheses and logical operators
    {"(ls -l) && (pwd)", "Parentheses with logical AND", 
        {TOKEN_OPEN_PAR, TOKEN_WORD, TOKEN_WORD, TOKEN_CLOSE_PAR, TOKEN_AND, 
        TOKEN_OPEN_PAR, TOKEN_WORD, TOKEN_CLOSE_PAR}, 
        {"(", "ls", "-l", ")", "&&", "(", "pwd", ")"}, 8},
    
    {"(echo hello) | (grep o) && pwd", "Parentheses with pipe and logical AND",
        {TOKEN_OPEN_PAR, TOKEN_WORD, TOKEN_WORD, TOKEN_CLOSE_PAR, TOKEN_PIPE,
        TOKEN_OPEN_PAR, TOKEN_WORD, TOKEN_WORD, TOKEN_CLOSE_PAR, TOKEN_AND, TOKEN_WORD},
        {"(", "echo", "hello", ")", "|", "(", "grep", "o", ")", "&&", "pwd"}, 11},

    // Quote handling with operators
    {"echo \"&&\"", "Quoted logical operator", 
        {TOKEN_WORD, TOKEN_WORD}, 
        {"echo", "\"&&\""}, 2},
    
    {"echo '&&'", "Single-quoted logical operator", 
        {TOKEN_WORD, TOKEN_WORD}, 
        {"echo", "'&&'"}, 2},
    
    {"echo \"(hello)\"", "Quoted parentheses", 
        {TOKEN_WORD, TOKEN_WORD}, 
        {"echo", "\"(hello)\""}, 2},

    // Mixed operator cases
    {"ls > file && cat file", "Redirect with logical AND", 
        {TOKEN_WORD, TOKEN_OUT, TOKEN_WORD, TOKEN_AND, TOKEN_WORD, TOKEN_WORD},
        {"ls", ">", "file", "&&", "cat", "file"}, 6},
    
    {"(ls > file) && (cat < file)", "Parentheses with redirections", 
        {TOKEN_OPEN_PAR, TOKEN_WORD, TOKEN_OUT, TOKEN_WORD, TOKEN_CLOSE_PAR, TOKEN_AND,
        TOKEN_OPEN_PAR, TOKEN_WORD, TOKEN_IN, TOKEN_WORD, TOKEN_CLOSE_PAR},
        {"(", "ls", ">", "file", ")", "&&", "(", "cat", "<", "file", ")"}, 11},

    // Error cases
    {"ls &&", "Dangling logical AND", 
        {TOKEN_WORD, TOKEN_AND}, 
        {"ls", "&&"}, 2},
    
    {"&& ls", "Leading logical AND", 
        {TOKEN_AND, TOKEN_WORD}, 
        {"&&", "ls"}, 2},
    
    {"(ls", "Unclosed parenthesis", 
        {TOKEN_OPEN_PAR, TOKEN_WORD}, 
        {"(", "ls"}, 2},
    
    {"ls)", "Unopened parenthesis", 
        {TOKEN_WORD, TOKEN_CLOSE_PAR}, 
        {"ls", ")"}, 2},

    // Complex nesting
    {"((ls && pwd) | (echo test && grep t))", "Complex nested expression",
        {TOKEN_OPEN_PAR, TOKEN_OPEN_PAR, TOKEN_WORD, TOKEN_AND, TOKEN_WORD, TOKEN_CLOSE_PAR,
        TOKEN_PIPE, TOKEN_OPEN_PAR, TOKEN_WORD, TOKEN_WORD, TOKEN_AND, TOKEN_WORD,
         TOKEN_WORD, TOKEN_CLOSE_PAR, TOKEN_CLOSE_PAR},
        {"(", "(", "ls", "&&", "pwd", ")", "|", "(", "echo", "test", "&&",
         "grep", "t", ")", ")"}, 15},

    // Edge cases with spaces
    {"ls&&pwd&&echo", "Multiple AND without spaces",
        {TOKEN_WORD, TOKEN_AND, TOKEN_WORD, TOKEN_AND, TOKEN_WORD},
        {"ls", "&&", "pwd", "&&", "echo"}, 5},
    
    {"(ls&&pwd)", "Parentheses with AND without spaces",
        {TOKEN_OPEN_PAR, TOKEN_WORD, TOKEN_AND, TOKEN_WORD, TOKEN_CLOSE_PAR},
        {"(", "ls", "&&", "pwd", ")"}, 5},

    // Mixed quotes and operators
    {"echo \"text && more\" && ls", "Quoted AND with real AND",
        {TOKEN_WORD, TOKEN_WORD, TOKEN_AND, TOKEN_WORD},
        {"echo", "\"text && more\"", "&&", "ls"}, 4},
    
    {"echo 'text && more' && ls", "Single-quoted AND with real AND",
        {TOKEN_WORD, TOKEN_WORD, TOKEN_AND, TOKEN_WORD},
        {"echo", "'text && more'", "&&", "ls"}, 4},

    // Special combinations
    {"(ls>file&&pwd)", "Parentheses with redirect and AND without spaces",
        {TOKEN_OPEN_PAR, TOKEN_WORD, TOKEN_OUT, TOKEN_WORD, TOKEN_AND, TOKEN_WORD, TOKEN_CLOSE_PAR},
        {"(", "ls", ">", "file", "&&", "pwd", ")"}, 7},

    {NULL, NULL, {0}, {0}, 0}  // Terminator case
};

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
		printf("%s🚨 Test not passed successfully\n%s", RED, RESET);
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
		printf("%s✅ Test passed successfully\n%s", GREEN, RESET);
	else
		printf("%s🚨 Test not passed successfully\n%s", RED, RESET);
	// Print actual tokens for reference
	print_tokens_formatted(tokens);
	printf("----------------------\n");
}

static void	run_test_suite(t_token **tokens, t_data *data)
{
	int		total_tests;
	int		passed_tests;
	t_token	*tmp;
	int		token_count;

	const char *failed_commands[50] = {0}; // Add this line
	int fail_count = 0;                    // Add this line
	total_tests = 0;
	passed_tests = 0;
	printf("\n=== Starting Tokenizer Test Suite ===\n");
	for (int i = 0; test_cases[i].input != NULL; i++)
	{
		bool test_passed = true; // Add this line
		*tokens = NULL;
		if (tokenize_input(test_cases[i].input, tokens, data))
		{
			printf("❌ Test %d failed: Could not tokenize input\n", i + 1);
			failed_commands[fail_count++] = test_cases[i].input;
			// Add this line
			continue ;
		}
		// Add token count validation
		tmp = *tokens;
		token_count = 0;
		while (tmp)
		{
			token_count++;
			tmp = tmp->next;
		}
		if (token_count != test_cases[i].expected_token_count)
		{
			test_passed = false;
			failed_commands[fail_count++] = test_cases[i].input;
		}
		validate_test_case(*tokens, &test_cases[i]);
		total_tests++;
		if (test_passed)    // Add this line
			passed_tests++; // Add this line
	}
	// Add summary section
	printf("\n=== Test Suite Summary ===\n");
	printf("Total tests:  %d\n", total_tests);
	printf("Passed tests: %d\n", passed_tests);
	printf("Failed tests: %d\n", total_tests - passed_tests);
	if (fail_count > 0)
	{
		printf("\nFailed commands:\n");
		for (int i = 0; i < fail_count; i++)
		{
			printf("  - \"%s\"\n", failed_commands[i]);
		}
	}
	else
	{
		printf("\n✅ All tests passed successfully!\n");
	}
	printf("\n=== End of Test Suite ===\n");
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_token	*tokens;

	ft_memset(&data, 0, sizeof(t_data));
	if (argv[1] && ft_strcmp(argv[1], "debug") == 0)
		launch_program(&data);
	else
		run_test_suite(&tokens, &data);
	return (0);
}
