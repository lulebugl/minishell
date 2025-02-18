/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:19:54 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/18 14:50:41 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include "minishell.h"

void	sigint_prompt_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_newline(int signum)
{
	(void)signum;
	write(1, "\n", 1);
}

void	init_signals(int pid)
{
	struct sigaction	act;
	
	ft_bzero(&act, sizeof(act));
	if (pid == 0)
	{
		act.sa_handler = &sigint_prompt_handler;
		sigaction(SIGINT, &act, NULL);
		act.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &act, NULL);
	}
	if (pid == 1)
	{
		act.sa_handler = sig_newline;
		sigaction(SIGINT, &act, NULL);
		sigaction(SIGQUIT, &act, NULL);
	}
}