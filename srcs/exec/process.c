/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:42:48 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/04 19:33:01 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_data *data, t_command *cmd, t_exec *exec, bool last)
{
	char	*cmd_path;
	char	**envp;

	if (exec->fd_in != STDIN_FILENO)
	{
		if (dup2(exec->fd_in, STDIN_FILENO) == -1)
			err_and_exit(data);
		close(exec->fd_in);
	}
	// Setup output redirection
	if (!last)
	{
		if (dup2(exec->fd_out, STDOUT_FILENO) == -1)
			err_and_exit(data);
		close(exec->pipe[0]);
		close(exec->pipe[1]);
	}
	// Close pipe fds in child
	if (exec->pipe[0] != -1)
		close(exec->pipe[0]);
	if (exec->pipe[1] != -1)
		close(exec->pipe[1]);
	dprintf(2, "here\n");
	cmd_path = get_path(cmd->args[0], data->env);
	if (!cmd_path)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: command not found\n",
			cmd->args[0]);
		exit(127);
	}
	envp = t_env_to_envp(data->env);
	if (!envp)
	{
		free(cmd_path);
		err_and_exit(data);
	}
	execve(cmd_path, cmd->args, envp);
	ft_free_tab(envp);
	free(cmd_path);
	err_and_exit(data);
}

void	parent_process(t_exec *exec)
{
	// Close used pipe ends
	if (exec->pipe[0] != -1)
		close(exec->pipe[0]);
	if (exec->pipe[1] != -1)
		close(exec->pipe[1]);
}
