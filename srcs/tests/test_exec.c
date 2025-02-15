/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:01:18 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/13 17:41:57 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* test_parser.c */
#include "ast.h"
#include "exec.h"
#include "minishell.h"

int	exec(t_data *data);

int	exec_prompt(const char *prompt, t_data *data)
{
	t_token	*token_head;

	if (tokenize_input(prompt, &data->tokens, data))
		return (clear_tokens(&data->tokens), 1);
	data->status = validate_prompt(data->tokens);
	if (data->status)
		return (clear_tokens(&data->tokens), 1);
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
	data->status = exec(data);
	if (data->status)
		return (clear_tokens(&data->tokens), free_tree(data->ast), 1);
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

	(void)argc;
	(void)argv;
	ft_memset(&data, 0, sizeof(t_data));
	env_init(&data.env, envp);
	data.envp = envp;
	launch_program(&data);
	data_free(&data);
	return (0);
}

