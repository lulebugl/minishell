/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:01:18 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/30 22:30:51 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* test_parser.c */
#include "minishell.h"
#include "ast.h"

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

int	exec_prompt(const char *prompt, t_data *data)
{
    t_tree_node *ast;
	t_token		*token_head;

    if (ft_strncmp(prompt, "exit", 5) == 0)
		return (clean_memory(data), exit(0), 0);
	if (ft_strcmp((char*)prompt, "token") == 0)
		data->print_token ^= 1;
	if (ft_strcmp((char*)prompt, "ast") == 0)
		data->print_ast ^= 1;
	if (ft_strcmp((char *)prompt, "env") == 0)
		ft_env(data->env);
	if (tokenize_input(prompt, &data->tokens, data))
		return (clear_tokens(&data->tokens), 1);
	data->status = validate_prompt(data, data->tokens);
	if (data->status)
		return (clear_tokens(&data->tokens), 1);
	token_head = data->tokens;
	if (!data->tokens)
		return (0);
	ast = new_tree(data, &token_head);
    if (!ast)
        err_and_exit(data);
    //   if (expander(data))
	//		 err_and_exit(data);
	if (data->print_token)
		print_tokens_formatted(data->tokens);
    if (data->print_ast)
    	print_ast_lucas(ast, 0);
	clear_tokens(&data->tokens);
	free_tree(ast);
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
