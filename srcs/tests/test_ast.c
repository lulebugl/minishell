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

/* test_parser.c */
#include "minishell.h"
#include "ast.h"

t_ast_node *parse_tokens(t_token *tokens);


void test_parse(const char *input, t_data *data)
{
    t_ast_node *ast;

    printf("\nTesting input: \"%s\"\n", input);
    printf("----------------------------------------\n");

    // Use your existing tokenizer
    if (tokenize_input(input, &data->tokens, data))
    {
        printf("Error: Tokenization failed\n");
        return;
    }

    // Print tokens (using your existing function)
    printf("Tokens:\n");
    print_tokens_formatted(data->tokens);
    printf("\n");

    // Parse tokens into AST
    ast = parse_tokens(data->tokens);
    if (!ast)
    {
        printf("Error: Parsing failed\n");
        clear_tokens(&data->tokens);
        return;
    }

    // Print resulting AST
    printf("AST Structure:\n");
    print_ast(ast, 0);
    printf("\n");

    // Cleanup
    free_ast(ast);
    clear_tokens(&data->tokens);
}

void	clean_memory(t_data *data)
{
	if (data)
	{
		if (data->env)
			env_free(data->env);
		clear_tokens(&data->tokens);
	}
}

void	err_and_exit(t_data *data)
{
	perror(strerror(errno));
	clean_memory(data);
	exit(EXIT_FAILURE);
}

/*
* i need to create function that clears everything without 
* exiting and set the exit status
* i.e when a syntax error occurs we display the error but give the prompt back 
** same for exec errors
*/

int	exec_prompt(const char *prompt, t_data *data)
{
	if (ft_strncmp(prompt, "exit", 5) == 0)
		return (clean_memory(data), exit(0), 0);
	if (ft_strcmp((char*)prompt, "token") == 0)
		data->print_token ^= 1;
	if (ft_strcmp((char *)prompt, "env") == 0)
		ft_env(data->env);
	if (tokenize_input(prompt, &data->tokens, data))
		return (clear_tokens(&data->tokens), 1);
	data->status = validate_prompt(data, data->tokens);
	if (data->status)
		return (clear_tokens(&data->tokens), 1);

	/* Parse tokens into AST */
    t_ast_node *ast;
	ast = parse_tokens(data->tokens);
    if (!ast)
    {
        printf("Error: Parsing failed\n");
        err_and_exit(data);
    }
    printf("AST Structure:\n");
    print_ast(ast, 0);
    printf("\n");
    /* end */

    if (expander(data))
		err_and_exit(data);
	if (data->print_token)
		print_tokens_formatted(data->tokens);
	clear_tokens(&data->tokens);
	return (0);
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
	clean_memory(&data);
	return (0);
}

// int main(void)
// {
//     t_data data;

//     ft_memset(&data, 0, sizeof(t_data));

//     // Test cases
//     test_parse("test || ls && echo", &data);
//     test_parse("ls -l | grep .c && echo done", &data);
//     test_parse("ls || cat file | grep test && echo ok", &data);
    
//     return 0;
// }