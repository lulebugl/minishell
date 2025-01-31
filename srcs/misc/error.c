/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:56:06 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/30 22:39:59 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msg_unexpected_token(char *str)
{
	char	*s;

	if (!str)
		s = "newline";
	else if (ft_strcmp(str, "\n") == 0)
		s = "newline";
	else
		s = str;
	ft_printf_fd(STDERR_FILENO,
		"minishell: syntax error near unexpected token `%s'\n", s);
	// else
	// 	ft_printf_fd(STDERR_FILENO,
	// 		"minishell: syntax error near unexpected token `%c'\n", token);
}

void	msg_custom_err(char *msg, char *details)
{
	ft_printf_fd(STDERR_FILENO, "minishell: ");
	if (details)
		ft_printf_fd(STDERR_FILENO, details);
	if (msg)
		ft_printf_fd(STDERR_FILENO, msg);
}

