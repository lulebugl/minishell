/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:58:43 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/20 19:48:16 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_exec(t_exec *exec)
{
	if (exec->fd_in != STDIN_FILENO)
		close(exec->fd_in);
	if (exec->pipe[0] != -1)
		close(exec->pipe[0]);
	if (exec->pipe[1] != -1)
		close(exec->pipe[1]);
	if (exec->waitlist)
		clear_waitlist(exec->waitlist);
	if (exec->child_pids)
		free(exec->child_pids);
}

void	init_exec(t_data *data, t_exec *exec, t_list **waitlist)
{
	ft_memset(exec, 0, sizeof(t_exec));
	// exec->child_count = ft_lstsize(*waitlist);
	exec->child_pids = malloc(sizeof(pid_t) * ft_lstsize(*waitlist));
	if (!exec->child_pids)
		err_and_exit(data);
	ft_memset(exec->child_pids, 0, sizeof(int) * ft_lstsize(*waitlist));
	exec->fd_in = STDIN_FILENO;
	exec->fd_out = STDOUT_FILENO;
	exec->id = 0;
	exec->pipe[0] = -1;
	exec->pipe[1] = -1;
	exec->waitlist = waitlist;
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

void	restore_fd(t_data *data)
{
	if (data->saved_stdin != -1)
	{
		dup2(data->saved_stdin, STDIN_FILENO);
		close(data->saved_stdin);
		data->saved_stdin = -1;
	}
	if (data->saved_stdout != -1)
	{
		dup2(data->saved_stdout, STDOUT_FILENO);
		close(data->saved_stdout);
		data->saved_stdout = -1;
	}
}
