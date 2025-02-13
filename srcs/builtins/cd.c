/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:31:25 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/13 20:53:47 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

static int	set_path(t_env *env, char **args, char **path)
{
	if (count_args(args) > 1)
		return (printf("minishell: cd: too many arguments\n"), ERROR);
	if (count_args(args) == 0)
		*path = env_get_value(env, "HOME");
	else if (count_args(args) == 1)
		*path = args[0];
	if (!*path)
		return (printf("minishell: cd: HOME NOT SET\n"), ERROR);
	if (ft_strcmp(*path, "-") == 0)
	{
		if (env_key_exists(env, "OLDPWD"))
			*path = env_get_value(env, "OLDPWD");
		else
			return (printf("minishell: cd: OLDPWD not set\n"), ERROR);
	}
	return (SUCCESS);
}

int	ft_cd(t_env *env, char **args)
{
	int		ret;
	char	*path;
	char	curr[PATH_MAX];

	if (!args)
		return (ERROR);
	getcwd(curr, PATH_MAX);
	if (!curr)
		return (ERROR);
	if (set_path(env, &args[1], &path) == ERROR)
		return (ERROR);
	ret = chdir(path);
	if (ret != 0)
		return (ft_printf_fd(STDERR_FILENO,
				"minishell: cd: %s: %s\n", path, strerror(errno)), ERROR);
	env_add_key(&env, "OLDPWD", ft_strdup(curr));
	getcwd(curr, PATH_MAX);
	if (!curr)
		return (ERROR);
	env_add_key(&env, "PWD", ft_strdup(curr));
	return (SUCCESS);
}
