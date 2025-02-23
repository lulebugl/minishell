/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:56:49 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/20 17:14:41 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_sig = 0;

void	sigint_handler(int sig)
{
	pid_t	pid;
	int		status;

	g_sig = sig;
	pid = waitpid(-1, &status, 0);
	if (WTERMSIG(status) == SIGINT || (pid > 0 && (WIFSIGNALED(status)
				&& WTERMSIG(status) == SIGINT)))
		write(2, "\n", 1);
	else
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		print_details();
		rl_redisplay();
	}
	g_sig = sig;
}

void	sigquit_handler(int sig)
{
	g_sig = sig;
	write(2, "Quit\n", 5);
}

int	exec_prompt(const char *prompt, t_data *data)
{
	t_token	*token_head;

	if (tokenize_input(prompt, &data->tokens, data))
		return (clear_tokens(&data->tokens), 1);
	data->status = validate_prompt(data->tokens);
	if (data->status)
		return (data->exit_code = data->status, clear_tokens(&data->tokens), 1);
	token_head = data->tokens;
	if (!data->tokens)
		return (0);
	data->ast = new_tree(data, &token_head);
	if (!data->ast)
		err_and_exit(data);
	if (data->print_token)
		print_tokens_formatted(data->tokens);
	if (data->print_ast)
		print_ast(data->ast, 0);
	exec(data);
	return (reset_data(data), 0);
}

int	launch_program(t_data *data)
{
	char	*rl;

	while (true)
	{
		init_signals();
		if (g_sig)
		{
			data->exit_code = g_sig + 128;
			g_sig = 0;
			reset_sigquit();
			continue ;
		}
		print_details();
		rl = readline(PROMPT3);
		reset_sigquit();
		if (!rl)
		{
			// ctrl-D
			printf("What\n");
			if (data->exit_code == 0)
				return (1);
			// ctrl-C
			else
				return (1);
		}
		if (rl && rl[0] == '\0')
		{
			free(rl);
			continue ;
		}
		data->rl = rl;
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
	data_init(&data);
	env_init(&data.env, envp);
	launch_program(&data);
	data_free(&data);
	return (0);
}

