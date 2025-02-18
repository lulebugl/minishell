/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:19:54 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/18 16:40:13 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void sigint_handler(int sig)
{
	pid_t	pid;
	int		status;
	
	(void)sig;
	pid = waitpid(-1, &status, 0);
	if (pid > 0 && (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT))
	{
		write(2, "\n", 1);
	}
	else
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals(void)
{
	struct sigaction	act;
	(void)pid;
	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sigint_handler;
	sigaction(SIGINT, &act, NULL);
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}
