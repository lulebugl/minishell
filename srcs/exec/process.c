/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:42:48 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/04 21:53:22 by llebugle         ###   ########.fr       */
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
    if (!last && exec->pipe[1] != STDOUT_FILENO)
    {
        if (dup2(exec->pipe[1], STDOUT_FILENO) == -1)
            err_and_exit(data);
    }

    if (exec->pipe[0] != -1)
        close(exec->pipe[0]);
    if (exec->pipe[1] != -1)
        close(exec->pipe[1]);
	cmd_path = get_path(cmd->arg_lst->content, data->env);
	if (!cmd_path)
	{
		if (cmd->arg_lst->content)
			ft_printf_fd(STDERR_FILENO, "minishell: %s: command not found\n",
				cmd->arg_lst->content);
		exit(127);
	}
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

// void	parent_process(t_exec *exec, bool last)
// {
// 	// Close old pipe fds if they exist
// 	if (exec->prev_pipe[0] != -1)
// 		close(exec->prev_pipe[0]);
// 	if (exec->prev_pipe[1] != -1)
// 		close(exec->prev_pipe[1]);
// 	if (!last)
// 	{
// 		// Store current pipe as previous for next iteration
// 		exec->prev_pipe[0] = exec->pipe[0];
// 		exec->prev_pipe[1] = exec->pipe[1];
// 	}
// }

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
        // Parent process
        if (exec->fd_in != STDIN_FILENO)
            close(exec->fd_in);

        if (!last)
        {
            close(exec->pipe[1]);
            exec->fd_in = exec->pipe[0];  // Save read end for next command
        }
        exec->child_pids[exec->id++] = exec->pid;
    }
	debug_cmd(data, cmd);
	// remember to close fds
	return (0);
}