/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 22:23:44 by maxweert          #+#    #+#             */
/*   Updated: 2025/01/27 14:50:04 by maxweert         ###   ########.fr       */
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
