/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:56:49 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/22 16:10:03 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_prompt(const char *prompt, t_data *data)
{
	t_token	*token_head;
	
	if (tokenize_input(prompt, &data->tokens, data))
		return (clear_tokens(&data->tokens), 1);
	data->status = validate_prompt(data, data->tokens);
	if (data->status)
		return (data->exit_code = data->status, clear_tokens(&data->tokens), 1);
	token_head = data->tokens;
	if (!data->tokens) // shouldn't be needed
		return (0);
	data->ast = new_tree(data, &token_head);
	if (!data->ast)
		err_and_exit(data);
	if (data->print_token)
		print_tokens_formatted(data->tokens);
	if (data->print_ast)
		print_ast(data->ast, 0);
	exec(data);
	// if (data->status)
	// 	return (clear_tokens(&data->tokens), free_tree(data->ast), 1);
	return (reset_data(data), 0);
}

int	launch_program(t_data *data)
{
	char	*rl;

	init_signals();
	while (true)
	{
		rl = readline(PROMPT);
		if (!rl)
			exit(1);
		add_history(rl);
		exec_prompt(rl, data);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	env_init(&data.env, envp);
	launch_program(&data);
	data_free(&data);
	return (0);
}


// typedef struct s_test_case
// {
// 	char	*input;
// 	char	*expected_output;
// }			t_test_case;

// void	print_test_result(const char *test_name, const char *input,
// 		const char *expected, const char *got, bool success)
// {
// 	printf("\n%s:\n", test_name);
// 	printf("Input: \"%s\"\n", input);
// 	printf("Expected: \"%s\"\n", expected);
// 	printf("Got: \"%s\"\n", got);
// 	if (success)
// 		printf("\033[0;32m[OK]\033[0m\n");
// 	else
// 		printf("\033[0;31m[KO]\033[0m\n");
// }

// char	*get_token_content(t_token *tokens)
// {
// 	if (!tokens || !tokens->content)
// 		return (NULL);
// 	return (tokens->content);
// }

// bool	run_test(t_data *data, const char *test_name, const char *input,
// 		const char *expected)
// {
// 	bool	success;
// 	char	*result;

// 	if (tokenize_input(input, &data->tokens, data))
// 		return (false);
// 	if (expander(data))
// 	{
// 		clear_tokens(&data->tokens);
// 		return (false);
// 	}
// 	result = get_token_content(data->tokens);
// 	success = (result && strcmp(result, expected) == 0);
// 	print_test_result(test_name, input, expected, result ? result : "NULL",
// 		success);
// 	clear_tokens(&data->tokens);
// 	return (success);
// }

// int	run_test_suite(t_data *data)
// {
// 	int		passed;
// 	int		total;
// 	char	expected[1024];

// 	passed = 0;
// 	total = 0;
// 	t_test_case tests[] = {
// 		// Basic environment variable expansion
// 		{"$USER", getenv("USER")},
// 		{"$HOME", getenv("HOME")},
// 		// Empty/undefined variables (bash removes them)
// 		{"$NONEXISTENT", ""},
// 		{"hello$NONEXISTENT", "hello"},
// 		{"$NONEXISTENThello", ""},
// 		// Quote handling
// 		{"\"$USER\"", getenv("USER")},
// 		{"'$USER'", "$USER"},
// 		{"'$HOME'", "$HOME"},
// 		{"\"$HOME\"", getenv("HOME")},
// 		// Mixed quotes
// 		{"\"$USER'$HOME'\"", NULL}, // Will construct dynamically
// 		{"'$USER\"$HOME\"'", "$USER\"$HOME\""},
// 		// Dollar sign edge cases
// 		{"$", "$"},
// 		{"$?", "0"},
// 		{"\"$\"", "$"},
// 		{"'$'", "$"},
// 		// {"$_", ""},  // Bash typically has this set but we'll expect empty
// 		// Variable boundaries
// 		{"$USER_NAME", ""}, // Bash treats underscore as part of var name
// 		{"$USER_", ""},
// 		{"$USER.", NULL}, // Will construct dynamically
// 		{"$USER/", NULL}, // Will construct dynamically
// 		// Complex combinations with spaces
// 		{"\"The user is $USER\"", NULL}, // Will construct dynamically
// 		{"'The user is $USER'", "The user is $USER"},
// 		// {"The user is $USER", NULL},      // Will construct dynamically
// 		{NULL, NULL} // End marker
// 	};
// 	printf("\nRunning expander tests...\n");
// 	printf("========================\n");
// 	for (int i = 0; tests[i].input != NULL; i++)
// 	{
// 		total++;
// 		if (tests[i].expected_output)
// 		{
// 			if (run_test(data, tests[i].input, tests[i].input,
// 					tests[i].expected_output))
// 				passed++;
// 		}
// 		else
// 		{
// 			// Handle cases that need dynamic expected values
// 			if (strcmp(tests[i].input, "$USER $HOME") == 0)
// 				snprintf(expected, sizeof(expected), "%s %s", getenv("USER"),
// 					getenv("HOME"));
// 			else if (strcmp(tests[i].input, "$USER  $HOME") == 0)
// 				snprintf(expected, sizeof(expected), "%s  %s", getenv("USER"),
// 					getenv("HOME"));
// 			else if (strcmp(tests[i].input, "\"$USER'$HOME'\"") == 0)
// 				snprintf(expected, sizeof(expected), "%s'%s'", getenv("USER"),
// 					getenv("HOME"));
// 			else if (strcmp(tests[i].input, "$USER.") == 0)
// 				snprintf(expected, sizeof(expected), "%s.", getenv("USER"));
// 			else if (strcmp(tests[i].input, "$USER/") == 0)
// 				snprintf(expected, sizeof(expected), "%s/", getenv("USER"));
// 			else if (strcmp(tests[i].input, "\"The user is $USER\"") == 0)
// 				snprintf(expected, sizeof(expected), "The user is %s",
// 					getenv("USER"));
// 			else if (strcmp(tests[i].input, "The user is $USER") == 0)
// 				snprintf(expected, sizeof(expected), "The user is %s",
// 					getenv("USER"));
// 			if (run_test(data, tests[i].input, tests[i].input, expected))
// 				passed++;
// 		}
// 	}
// 	printf("\nTest Results: %d/%d passed\n", passed, total);
// 	return (passed == total ? 0 : 1);
// }