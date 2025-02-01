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


void	err_and_exit(t_data *data)
{
	perror(strerror(errno));
	data_free(data);
	exit(EXIT_FAILURE);
}

void	msg_unexpected_token(char *str)
{
	const char	*s;

	if (!str || ft_strcmp(str, "\n") == 0)
		s = "newline";
	else
		s = str;
	ft_printf_fd(STDERR_FILENO,
		"minishell: syntax error near unexpected token `%s'\n", s);
}

void	msg_custom_err(char *msg, char *details)
{
	ft_printf_fd(STDERR_FILENO, "minishell: ");
	if (details)
		ft_printf_fd(STDERR_FILENO, details);
	if (msg)
		ft_printf_fd(STDERR_FILENO, msg);
}

