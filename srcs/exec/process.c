/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:42:48 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/19 15:49:29 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_fds(t_data *data, t_exec *exec, bool last)
{
	if (exec->fd_in != STDIN_FILENO)
	{
		if (dup2(exec->fd_in, STDIN_FILENO) == -1)
			err_and_exit(data);
		close(exec->fd_in);
	}
	if (!last)
	{
		if (dup2(exec->pipe[1], STDOUT_FILENO) == -1)
			err_and_exit(data);
		close(exec->pipe[1]);
	}
}

void	child_process(t_data *data, t_command *cmd, t_exec *exec, bool last)
{
	char	*cmd_path;
	char	**envp;

	dup_fds(data, exec, last);
	if (exec->pipe[0] != -1)
		close(exec->pipe[0]);
	if (exec->pipe[1] != -1)
		close(exec->pipe[1]);
	if (redirect_fd(data, cmd) == ERROR)
		exit(1);
	if (exec_builtin(data, cmd))
		ft_exit(data, NULL);
	cmd_path = get_path(data, cmd->arg_lst->content, data->env);
	if (!cmd_path)
		cmd_path = try_relative(data, cmd->arg_lst->content);
	envp = t_env_to_envp(data->env);
	if (!envp)
	{
		free(cmd_path);
		err_and_exit(data);
	}
	execve(cmd_path, get_cmd_args_arr(cmd), envp);
	ft_free_tab(envp);
	free(cmd_path);
	err_and_exit(data);
}



