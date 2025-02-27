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

// char	*try_relative(t_data *data, char *str, t_exec *exec)
// {
// 	char	*valid_path;

// 	valid_path = ft_strjoin("./", str);
// 	if (!access(str, F_OK) && access(str, X_OK))
// 	{
// 		ft_printf_fd(STDERR_FILENO, "minishell: %s: Permission denied\n", str);
// 		free(valid_path);
// 		data_free(data);
// 		cleanup_exec(exec);
// 		exit(126);
// 	}
// 	if (!valid_path)
// 		return (err_and_exit(data), NULL);
// 	if (access(valid_path, F_OK) == -1)
// 	{
// 		ft_printf_fd(STDERR_FILENO, "minishell: %s: command not found\n", str);
// 		free(valid_path);
// 		data_free(data);
// 		cleanup_exec(exec);
// 		exit(127);
// 	}
// 	if (!access(valid_path, F_OK) && access(valid_path, X_OK))
// 	{
// 		ft_printf_fd(STDERR_FILENO, "minishell: %s: Permission denied\n", str);
// 		free(valid_path);
// 		data_free(data);
// 		cleanup_exec(exec);
// 		exit(126);
// 	}
// 	return (valid_path);
// }

char	*try_relative(t_data *data, char *str, t_exec *exec)
{
	if (!access(str, F_OK) && access(str, X_OK))
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: Permission denied\n", str);
		data_free(data);
		cleanup_exec(exec);
		exit(126);
	}
	if (access(str, F_OK) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: command not found\n", str);
		data_free(data);
		cleanup_exec(exec);
		exit(127);
	}
	if (!access(str, F_OK) && access(str, X_OK))
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: Permission denied\n", str);
		data_free(data);
		cleanup_exec(exec);
		exit(126);
	}
	return (str);
}

static char	*try_path(t_data *data, char *str, char *env)
{
	int		i;
	char	**path;
	char	*valid_path;
	char	*tmp;

	i = -1;
	valid_path = NULL;
	path = ft_split(env, ':');
	if (!path)
		return (err_and_exit(data), NULL);
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		valid_path = ft_strjoin_n_free(tmp, str);
		if (access(valid_path, F_OK) == 0)
			break ;
		free(valid_path);
		valid_path = NULL;
	}
	ft_free_tab(path);
	return (valid_path);
}

char	*get_path(t_data *data, char *str, t_env *env)
{
	int		i;
	t_env	*curr;

	i = 0;
	curr = env;
	if (!str)
		return (NULL);
	if (access(str, F_OK) == 0 && !is_dir(str) && access(str, X_OK) == 0)
		return (ft_strdup(str));
	while (curr)
	{
		if (curr->key && ft_strncmp(curr->key, "PATH", 4) == 0)
			return (try_path(data, str, curr->value));
		curr = curr->next;
	}
	return (NULL);
}

