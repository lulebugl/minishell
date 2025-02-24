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

void	signal_ctlc(int sig)
{
	g_sig = sig;

	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		print_details();
		rl_redisplay();
	}
}

void	signal_ctlc_heredoc(int sig)
{
	g_sig = sig;
	
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	exec_prompt(const char *prompt, t_data *data)
{
	t_token	*token_head;

	signal(SIGINT, SIG_IGN);
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
		return (reset_data(data), 0);
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

	signal(SIGQUIT, SIG_IGN);
	while (true)
	{
		signal(SIGINT, signal_ctlc);
		termios_change(false);
		if (g_sig)
		{
			data->exit_code = g_sig + 128;
			g_sig = 0;
			continue ;
		}
		print_details();
		rl = readline(PROMPT3);
		if (!rl)
		{
			// ctrl-D
			termios_change(true);
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

