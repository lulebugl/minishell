/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:58:43 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/04 21:52:02 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_exec(t_data *data, t_exec *exec, int child_count)
{
	ft_memset(exec, 0, sizeof(t_exec));
	exec->child_pids = malloc(sizeof(pid_t) * child_count);
	if (!exec->child_pids)
		err_and_exit(data);
	exec->fd_in = STDIN_FILENO;
    exec->fd_out = STDOUT_FILENO;
    exec->id = 0;
    exec->pipe[0] = -1;
    exec->pipe[1] = -1;
    
    // Save original stdin/stdout
    // exec->stdin_backup = dup(STDIN_FILENO);
    // exec->stdout_backup = dup(STDOUT_FILENO);
}

void	wait_child(t_data *data, pid_t *child_pids, int child_count)
{
	int	i;
	int	status;

	i = 0;
	while (i < child_count)
	{
		if (child_pids[i] > 0)
		{
			waitpid(child_pids[i], &status, 0);
			if (WIFEXITED(status))
				data->status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->status = 128 + WTERMSIG(status);
		}
		i++;
	}
	if (data->exec_debug)
		printf("All children have terminated\n");
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

	curr = env;
	i = 1;
	while (curr)
	{
		curr = curr->next;
		i++;
	}
	envp = (char **)malloc(sizeof(char *) * i);
	// ft_bzero(envp, (sizeof(char *) * i));
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
		// printf("%s\n", envp[i]);
		if (!envp[i])
			return (ft_free_tab(envp), NULL);
		curr = curr->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

