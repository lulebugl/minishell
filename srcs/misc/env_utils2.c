/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:57:10 by maxweert          #+#    #+#             */
/*   Updated: 2025/01/27 17:45:57 by maxweert         ###   ########.fr       */
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
		return (NULL);
	elem->key = key;
	elem->value = value;
	elem->next = NULL;
	return (elem);
}

/*
 * Function: env_add_key
 * ----------------------------
 * 	Add a new element in the env list.
 *	The value HAS to be malloced.
 */

void	env_add_key(t_env **env, char *key, char *value)
{
	t_env	*new;
	t_env	*head;

	if (!key)
		return ;
	if (env_key_exists(*env, key))
	{
		env_update_key(*env, key, value);
		return ;
	}
	new = env_create_elem(key, value);
	if (!new)
		return ;
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
 * Function: env_update_key
 * ----------------------------
 *	Update an element in env list.
 */

void	env_update_key(t_env *env, char *key, char *value)
{
	if (!key)
		return ;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = value;
			break ;
		}
		env = env->next;
	}
}

/*
 * Function: env_key_exists
 * ----------------------------
 *	Check if an element exists in env list.
 */

int	env_key_exists(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}
