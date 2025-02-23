/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 22:23:44 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/20 19:16:06 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: get_env_var
 * ----------------------------
 *	Returns the value of a specified environment variable
 * 
 *	EXAMPLE : 
 *		if env contain USER=mweerts
 *		get_env_var(env, "USER") returns mweerts
 */

char	*env_get_value(t_env *env, char *key)
{
	if (!key || !key[0])
		return (NULL);
	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

/*
 * Function: env_key_from_str
 * ----------------------------
 *	Extract and returns the key from a string.
 *	!!! The return value is MALLOCED !!!
 */

char	*env_key_from_str(char *str)
{
	int		i;

	i = 0;
	if (!ft_strchr(str, '='))
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	return (ft_strndup(str, i));
}

/*
 * Function: env_value_from_str
 * ----------------------------
 *	Extract and returns the value from a string.
 *	!!! The return value is MALLOCED !!!
 */

char	*env_value_from_str(char *str)
{
	int		i;

	i = 0;
	if (!ft_strchr(str, '='))
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	return (ft_strdup(&str[i + 1]));
}

static void	env_update_shlvl(t_env **env)
{
	int		tmp;

	if (!env_key_exists(*env, "SHLVL"))
		env_add_key(env, "SHLVL", "1");
	else
	{
		tmp = ft_atoi(env_get_value(*env, "SHLVL"));
		if (tmp < 0)
			env_update_key(*env, "SHLVL", "0");
		else
			env_update_key(*env, "SHLVL", ft_itoa(tmp + 1));
	}
}

/*
 * Function: init_env
 * ----------------------------
 *	Initialize the list pointed by data->env with all environments variable
 *	The list stock variable as follow :
 *	KEY=VALUE	(ie USER=MWEERTS)
 *	env.key = KEY (USER)
 *	env.value = VALUE (MWEERTS)
 */

void	env_init(t_env **env, char **env_arr)
{
	int		i;
	char	curr[PATH_MAX];

	if (!env_arr || !env_arr[0])
	{
		*env = env_create_elem(ft_strdup("SHLVL"), ft_strdup("1"));
		if (!env)
			return ;
		(*env)->next = env_create_elem("PWD",
				ft_strdup(getcwd(curr, PATH_MAX)));
		return ;
	}
	i = 0;
	while (env_arr[i])
	{
		env_add_key(env, env_key_from_str(env_arr[i]),
			env_value_from_str(env_arr[i]));
		i++;
	}
	env_update_shlvl(env);
}
