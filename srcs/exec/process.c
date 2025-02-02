/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:42:48 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/02 16:42:50 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*try_path(char *str, char *env)
{
	int		i;
	char	**path;
	char	*valid_path;
	char	*tmp;

	i = -1;
	valid_path = NULL;
	path = ft_split(env, ':');
	if (!path)
		return (NULL);
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		valid_path = ft_strjoin_n_free(tmp, str);
		if (!valid_path)
			return (ft_free_tab(path), NULL);
		if (access(valid_path, F_OK) == 0)
			break ;
		free(valid_path);
		valid_path = NULL;
	}
	ft_free_tab(path);
	return (valid_path);
}

char	*get_path(char *str, t_env *env)
{
	int	i;
	t_env	*curr;
	
	i = 0;
	curr = env;
	if (!str)
		return (NULL);
	while (curr)
	{
		if (curr->key && ft_strncmp(curr->key, "PATH", 4) == 0)
			return (try_path(str, curr->value));
		curr = curr->next;
	}
	return (NULL);
}

void child_process(t_data *data, t_command *cmd, t_exec *exec)
{
    char *cmd_path;
    
    // Handle pipe redirection
    if (exec->pipe[0] != -1)
    {
        dup2(exec->pipe[0], STDIN_FILENO);
        close(exec->pipe[0]);
    }
    if (exec->pipe[1] != -1)
    {
        dup2(exec->pipe[1], STDOUT_FILENO);
        close(exec->pipe[1]);
    }
    
    // Close unused pipe ends
    if (exec->pipe[0] != -1)
        close(exec->pipe[0]);
        
    // Find command path
    cmd_path = get_path(cmd->args[0], data->env);
    if (!cmd_path)
    {
        ft_printf_fd(STDERR_FILENO, "minishell: %s: command not found\n", cmd->args[0]);
        exit(127);
    }
    
    // Execute command
    execve(cmd_path, cmd->args, data->envp);  // You'll want to add proper environment later
    
    // If execve returns, there was an error
    err_and_exit(data);
}

void parent_process(t_exec *exec)
{
    // Close used pipe ends
    if (exec->pipe[0] != -1)
        close(exec->pipe[0]);
    if (exec->pipe[1] != -1)
        close(exec->pipe[1]);
        
    // Update pipe_read for next command
    // exec->pipe_read = exec->pipe[0];
}
