/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:09:55 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/19 17:09:57 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_fd(t_data *data, t_command *cmd)
{
	t_redirection *curr;

	curr = cmd->redirections;
	while (curr)
	{
		if (curr->type == TOKEN_IN)
			process_infile();
		else if (curr->type == TOKEN_OUT)
			process_file();
		else if (curr->type == TOKEN_APPEND)
			process_infile();

		curr = curr->next;
	}
	return (0);
}
