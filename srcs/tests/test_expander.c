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
	data->status = validate_prompt(data->tokens);
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

	while (true)
	{
		init_signals(0);
		rl = readline(PROMPT);
		if (!rl)
		{
			// ctrl-D
			printf("what?");
			if (errno == 0)
				return (1);
			// ctrl-C
			else
				return (1);
		}
		// empty line
		if (rl && rl[0] == '\0')
		{
			free(rl);
			continue ;
		}
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
	launch_program(&data);
	data_free(&data);
	return (0);
}
