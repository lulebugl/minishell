/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:58:43 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/20 16:32:39 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_data *data, t_command *cmd)
{
	char	**argv;

	if (!cmd || !cmd->arg_lst || !cmd->arg_lst->content)
		return (0);
	argv = get_cmd_args_arr(cmd);
	if (!argv)
		return (0);
	if (ft_strcmp(cmd->arg_lst->content, "exit") == 0)
		data->exit_code = ft_exit(data, argv);
	else if (ft_strcmp(cmd->arg_lst->content, "pwd") == 0)
		data->exit_code = ft_pwd();
	else if (ft_strcmp(cmd->arg_lst->content, "cd") == 0)
		data->exit_code = ft_cd(data->env, argv);
	else if (ft_strcmp(cmd->arg_lst->content, "env") == 0)
		data->exit_code = ft_env(data->env);
	else if (ft_strcmp(cmd->arg_lst->content, "echo") == 0)
		data->exit_code = ft_echo(argv);
	else if (ft_strcmp(cmd->arg_lst->content, "export") == 0)
		data->exit_code = ft_export(data->env, argv);
	else if (ft_strcmp(cmd->arg_lst->content, "unset") == 0)
		data->exit_code = ft_unset(data->env, argv);
	else
		return (ft_free_tab(argv), 0);
	return (ft_free_tab(argv), 1);
}

bool	is_single_builtin(t_data *data, t_command *cmd)
{
	if (!cmd || !cmd->arg_lst || !cmd->arg_lst->content)
		return (0);
	if (ft_strcmp(cmd->arg_lst->content, "exit") == 0)
		return (true);
	else if (ft_strcmp(cmd->arg_lst->content, "pwd") == 0)
		return (true);
	else if (ft_strcmp(cmd->arg_lst->content, "cd") == 0)
		return (true);
	else if (ft_strcmp(cmd->arg_lst->content, "env") == 0)
		return (true);
	else if (ft_strcmp(cmd->arg_lst->content, "echo") == 0)
		return (true);
	else if (ft_strcmp(cmd->arg_lst->content, "export") == 0)
		return (true);
	else if (ft_strcmp(cmd->arg_lst->content, "unset") == 0)
		return (true);
	else
		return (false);
}

void	init_exec(t_data *data, t_exec *exec, int child_count)
{
	ft_memset(exec, 0, sizeof(t_exec));
	exec->child_pids = malloc(sizeof(pid_t) * child_count);
	if (!exec->child_pids)
		err_and_exit(data);
	ft_memset(exec->child_pids, 0, sizeof(int) * child_count);
	exec->fd_in = STDIN_FILENO;
	exec->fd_out = STDOUT_FILENO;
	exec->id = 0;
	exec->pipe[0] = -1;
	exec->pipe[1] = -1;
	reset_sigquit();
}

int	wait_child(pid_t *child_pids, int child_count)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	last_status = 0;
	while (i < child_count)
	{
		if (child_pids[i] > 0)
		{
			waitpid(child_pids[i], &status, 0);
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	free(child_pids);
	return (last_status);
}

int	get_env_size(t_env *env)
{
	int		size;
	t_env	*curr;

	if (!env)
		return (0);
	curr = env;
	size = 0;
	while (curr)
	{
		curr = curr->next;
		size++;
	}
	return (size);
}

/*
 * Function: t_env_to_envp
 * ----------------------------
 *	Convert linked list t_env to array envp[].
 */
char	**t_env_to_envp(t_env *env)
{
	char	**envp;
	int		i;
	t_env	*curr;

	envp = (char **)malloc(sizeof(char *) * (get_env_size(env) + 1));
	if (!envp)
		return (NULL);
	curr = env;
	i = 0;
	while (curr && curr->key)
	{
		envp[i] = ft_strjoin(curr->key, "=");
		if (!envp[i])
			return (ft_free_tab(envp), NULL);
		envp[i] = ft_strjoin_n_free(envp[i], curr->value);
		if (!envp[i])
			return (ft_free_tab(envp), NULL);
		curr = curr->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

