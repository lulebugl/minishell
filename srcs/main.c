/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:56:49 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/22 18:44:16 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (ft_strncmp(prompt, "exit", 5) == 0)
		return (clean_memory(data), exit(0), 0);
	if (ft_strcmp((char*)prompt, "token") == 0) 	// toggle on/off to print tokens
		data->print_token ^= 1;
	if (ft_strcmp((char *)prompt, "env") == 0)
		ft_env(data->env);
	if (tokenize_input(prompt, &data->tokens, data))
		return (clean_memory(data), 1);
	if (validate_prompt(data, data->tokens))
		return (clear_tokens(&data->tokens), 1);
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
	// env(data.env);
	// unset(data.env, argv[1]);
	// ft_export(data.env, &argv[1]);
	// ft_env(data.env);
	// free_env(&data);
	// ft_unset(data.env, &argv[1]);
	ft_echo(&argv[1]);
	clean_memory(&data);
	return (0);
}

