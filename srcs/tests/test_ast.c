/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:01:18 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/27 20:01:21 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"

void print_detailed_ast(t_ast_node *ast);

void test_ast(const char *input)
{
    t_data data;
    t_ast_node *ast;

    ft_memset(&data, 0, sizeof(t_data));

    printf("\n=== Testing input: \"%s\" ===\n", input);
    printf("----------------------------------------\n");

    // Tokenize the input
    if (tokenize_input(input, &data.tokens, &data))
    {
        printf("Error: Tokenization failed\n");
        return;
    }

    // Print tokens
    printf("Tokens:\n");
    print_tokens_formatted(data.tokens);
    printf("\n");

    // Build AST
    ast = build_ast(data.tokens);
    if (!ast)
    {
        printf("Error: AST construction failed\n");
        clear_tokens(&data.tokens);
        return;
    }

    // Print detailed node relationships
    print_detailed_ast(ast);

    // Cleanup
    free_ast(ast);
    clear_tokens(&data.tokens);
    printf("----------------------------------------\n");
}

int main(void)
{
    // Test simple command
    test_ast("ls -l");

    // Test single pipe
    test_ast("ls -l | grep .c");

    // Test two pipes
    test_ast("cat file.txt | grep pattern | wc -l");

    // Test three pipes
    test_ast("find . -name *.c | xargs grep TODO | sort | uniq -c");
    
    return (0);
}