/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:19:54 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/20 16:34:13 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
