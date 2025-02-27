/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:55:02 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/04 18:55:21 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dir(char *str)
{
	struct stat	st;

	if (stat(str, &st) != 0)
		return (0);
	return (S_ISDIR(st.st_mode));
}

void	error_path(t_data *data, t_exec *exec, char *path, int err)
{
	if (err == PERMISSION_DENIED)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: Permission denied\n", path);
	}
	else if (err == CMD_NOT_FOUND)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: command not found\n", path);
	}
	else if (err == NO_SUCH_FILE)
	{
		ft_printf_fd(STDERR_FILENO, \
			"minishell: %s: No such file or directory\n", path);
		// free(path);
	}
	cleanup_exec(exec);
	data_free(data);
	if (err == PERMISSION_DENIED)
		exit(126);
	exit(127);
}

char	*try_relative(t_data *data, char *path, t_exec *exec)
{
	if (!path)
		return (NULL);
	if (!access(path, F_OK) && access(path, X_OK))
		return (error_path(data, exec, path, PERMISSION_DENIED), NULL);
	if (access(path, F_OK) == -1)
		return (error_path(data, exec, path, CMD_NOT_FOUND), NULL);
	return (path);
}

static char	*try_path(t_data *data, char *str, char *env)
{
	int		i;
	char	**path;
	char	*found;
	char	*tmp;

	i = -1;
	found = NULL;
	if (str && (str[0] == '.' || str[0] == '/'))
		return (NULL);
	path = ft_split(env, ':');
	if (!path)
		return (err_and_exit(data), NULL);
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		found = ft_strjoin_n_free(tmp, str);
		if (access(found, F_OK) == 0 && !is_dir(found) && access(found,
				X_OK) == 0)
			break ;
		free(found);
		found = NULL;
	}
	ft_free_tab(path);
	return (found);
}

char	*get_path(t_data *data, t_command *cmd, t_exec *exec)
{
	int		i;
	t_env	*curr;
	char	*path;
	char	*found;

	i = 0;
	curr = data->env;
	if (!cmd || !cmd->arg_lst || !cmd->arg_lst->content)
		return (NULL);
	path = cmd->arg_lst->content;
	if (access(path, F_OK) == 0 && !is_dir(path) && access(path, X_OK) == 0)
		return (cmd->arg_lst->content);
	while (curr)
	{
		if (curr->key && ft_strncmp(curr->key, "PATH", 4) == 0)
		{
			found = try_path(data, path, curr->value);
			if (!found)
				break ;
			return (found);
		}
		curr = curr->next;
	}
	return (cmd->arg_lst->content);
}
