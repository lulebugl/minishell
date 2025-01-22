/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 22:23:44 by maxweert          #+#    #+#             */
/*   Updated: 2025/01/22 16:07:04 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: env_create_elem
 * ----------------------------
 *	Create new env elem.
 */

t_env	*env_create_elem(char *key, char *value)
{
	t_env	*elem;

	elem = (t_env *)malloc(sizeof(t_env));
	if (!elem)
		return (0);
	elem->key = key;
	elem->value = value;
	elem->next = NULL;
	return (elem);
}

/*
 * Function: add_env
 * ----------------------------
 *	Util function for init_env.
 * 	Just add a new element in the list.	
 */

void	env_add(t_env **env, char *str)
{
	t_env	*new;
	t_env	*head;
	char	**tmp;
	int		i;

	i = 0;
	if (!ft_strchr(str, '='))
		return ;
	while (str[i] && str[i] != '=')
		i++;
	new = env_create_elem(ft_strndup(str, i), ft_strdup(&str[i + 1]));
	head = *env;
	if (!head)
		*env = new;
	else
	{
		while (head->next)
			head = head->next;
		head->next = new;
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

	if (!env_arr || !env_arr[0])
		return ;
	i = 0;
	while (env_arr[i])
	{
		env_add(env, env_arr[i]);
		i++;
	}
}

/*
 * Function: free_env
 * ----------------------------
 *	Free the list pointed by data->env
 */

void	env_free(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

/*
 * Function: get_env_var
 * ----------------------------
 *	Returns the value of a specified environment variable
 * 
 *	EXAMPLE : 
 *		if env contain USER=mweerts
 *		get_env_var(env, "USER") returns mweerts
 */

char	*env_get_var(t_env *env, char *arg)
{
	while (env)
	{
		if (ft_strncmp(arg, env->key, ft_strlen(arg)) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
