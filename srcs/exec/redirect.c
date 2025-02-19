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

int	process_outfile(t_data *data, char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: %s\n", filename,
			strerror(errno));
		return (ERROR);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (ERROR);
	}
	return (SUCCESS);
}

int	redirect_fd(t_data *data, t_command *cmd)
{
	t_redirection	*curr;

	curr = cmd->redirections;
	while (curr)
	{
		if (curr->type == TOKEN_OUT)
		{
			if (process_outfile(data, curr->filename) == ERROR)
				return (data->exit_code = errno, ERROR);
		}
		// else if (curr->type == TOKEN_IN)
		// 	process_infile();
		// else if (curr->type == TOKEN_APPEND)
		// 	process_append();
		else
			return (ERROR);
		curr = curr->next;
	}
	return (0);
}

