/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:19:54 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/19 16:02:29 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler(int sig)
{
	pid_t	pid;
	int		status;

	(void)sig;
	pid = waitpid(-1, &status, 0);
	if (pid > 0 && (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT))
		write(2, "\n", 1);
	else
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	sigquit_handler(int sig)
{
	(void)sig;
	write(2, "Quit\n", 5);
}

void	reset_sigquit(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_flags = SA_RESTART;
	sigemptyset(&(act).sa_mask);
	act.sa_handler = &sigquit_handler;
	sigaction(SIGQUIT, &act, NULL);
}

void	init_signals(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_flags = SA_RESTART;
	sigemptyset(&(act).sa_mask);
	act.sa_handler = &sigint_handler;
	sigaction(SIGINT, &act, NULL);
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}
