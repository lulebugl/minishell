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

int	is_builtin(t_data *data, t_command *cmd)
{
	char **argv;
	
	if (!cmd || !cmd->arg_lst || !cmd->arg_lst->content)
		return (0);
	argv = get_cmd_args_arr(cmd);
	if (!argv)
		return (0);
	if (ft_strcmp(cmd->arg_lst->content, "exit") == 0)
		data->status = ft_exit(data, argv);
	else if (ft_strcmp(cmd->arg_lst->content, "pwd") == 0)
		data->status = ft_pwd();
	else if (ft_strcmp(cmd->arg_lst->content, "cd") == 0)
		data->status = ft_cd(data->env, argv);
	else if (ft_strcmp(cmd->arg_lst->content, "env") == 0)
		data->status = ft_env(data->env);
	else if (ft_strcmp(cmd->arg_lst->content, "echo") == 0)
		data->status = ft_echo(argv);
	else if (ft_strcmp(cmd->arg_lst->content, "export") == 0)
		data->status = ft_export(data->env, argv);
	else if (ft_strcmp(cmd->arg_lst->content, "unset") == 0)
		data->status = ft_unset(data->env, argv);
	else
		return (ft_free_tab(argv), 0);
	return (ft_free_tab(argv), 1);
}

void	dup_fds(t_data *data, t_exec *exec, bool last)
{
	if (exec->fd_in != STDIN_FILENO)
	{
		if (dup2(exec->fd_in, STDIN_FILENO) == -1)
			err_and_exit(data);
		close(exec->fd_in);
	}
	if (!last) // Remove the exec->pipe[1] != STDOUT_FILENO check
	{
		if (dup2(exec->pipe[1], STDOUT_FILENO) == -1)
			err_and_exit(data);
		close(exec->pipe[1]); // Add this to close the pipe after duplication
	}
}

void	child_process(t_data *data, t_command *cmd, t_exec *exec, bool last)
{
	char	*cmd_path;
	char	**envp;

	dup_fds(data, exec, last);
	// implementer redirections
	if (exec->pipe[0] != -1)
		close(exec->pipe[0]);
	if (exec->pipe[1] != -1)
		close(exec->pipe[1]);
	if (is_builtin(data, cmd))
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

int	exec_cmd(t_data *data, t_command *cmd, t_exec *exec, bool last)
{
	if (!cmd)
		return (1);
	if (!last)
		if (pipe(exec->pipe) == -1)
			err_and_exit(data);
	exec->pid = fork();
	if (exec->pid < 0)
		err_and_exit(data);
	if (exec->pid == 0)
		child_process(data, cmd, exec, last);
	else
	{
		if (exec->fd_in != STDIN_FILENO)
			close(exec->fd_in);
		if (!last)
		{
			close(exec->pipe[1]);
			exec->fd_in = exec->pipe[0]; // Save read end for next command
		}
		exec->child_pids[exec->id++] = exec->pid;
	}
	debug_cmd(data, cmd); // remove at the end
	// remember to close fds
	return (0);
}

