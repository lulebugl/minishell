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
#include "../../includes/minishell.h"

// Helper function to print tokens in a clear format
void print_tokens_formatted(t_token *tokens) {
    t_token *current = tokens;
    int token_count = 0;
    
    printf("\n=== Token List ===\n");
    if (!current)
        printf("No tokens found.\n");
    
    while (current) {
        printf("Token[%d]: '%s'\n", token_count, (char *)current->content);
        current = current->next;
        token_count++;
    }
    printf("================\n");
}

// Helper function to free token list
void free_tokens(t_token *tokens) {
    t_token *current = tokens;
    while (current) {
        t_token *next = current->next;
        free(current->content);
        free(current);
        current = next;
    }
}

void test_arg_input(const char *input) {
    t_token *tokens = NULL;
    
    printf("Input string: \"%s\"\n", input);
    printf(PURPLE);
    tokenize_input(input, &tokens);
    printf(RESET);
    
    print_tokens_formatted(tokens);
    free_tokens(tokens);
}

void run_basic_tests() {
    t_token *tokens = NULL;
    
    // Test 1: Basic input
    printf("\n--- Test 1: Basic Input ---\n");
    tokens = NULL;
    tokenize_input("echo hello world", &tokens);
    print_tokens_formatted(tokens);
    free_tokens(tokens);

    // Test 2: Multiple spaces
    printf("\n--- Test 2: Multiple Spaces ---\n");
    tokens = NULL;
    tokenize_input("ls   -l     /home", &tokens);
    print_tokens_formatted(tokens);
    free_tokens(tokens);

    // Test 3: Leading/trailing spaces
    printf("\n--- Test 3: Leading/Trailing Spaces ---\n");
    tokens = NULL;
    tokenize_input("   cat test.txt   ",&tokens);
    print_tokens_formatted(tokens);
    free_tokens(tokens);

    // Test 4: Empty input
    printf("\n--- Test 4: Empty Input ---\n");
    tokens = NULL;
    tokenize_input("", &tokens);
    print_tokens_formatted(tokens);
    free_tokens(tokens);
}

// int main(int argc, char **argv) {
//     printf("=== Minishell Lexer Test ===\n");

//     // Test command line argument if provided
//     if (argc > 1) {
//         test_arg_input(argv[1]);
//         return 0;
//     }
    
//     // If no arguments provided, run all basic tests
//     printf("\nNo argument provided. Running basic test suite...\n");
//     run_basic_tests();
    
//     return 0;
// }

int exec_prompt(const char *prompt)
{
	if (ft_strncmp(prompt, "exit", 5) == 0)
		exit(0);
	test_arg_input(prompt);
	
	return (0);
}

int launch_program(t_data *data)
{
	while (true)
	{
		char *rl;
		
		rl = readline(PROMPT);
		if (!rl)
			exit(1);
		exec_prompt(rl);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data data;
	
	ft_memset(&data, 0, sizeof(t_data));
	launch_program(&data);
	return (0);
}