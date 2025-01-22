/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 02:30:53 by maxweert          #+#    #+#             */
/*   Updated: 2025/01/22 03:34:49 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: remove_env_elem
 * ----------------------------
 *	Util function to remove and free an elem from env list.
 */

static void remove_env_elem(t_env **env, char *key)
{
	t_env	*head;
	t_env	*previous;
	t_env	*tmp;

	head = *env;
	previous = NULL;
	while (head)
	{
		if (ft_strncmp(key, head->key, ft_strlen(key)) == 0)
		{
			tmp = head->next;
			free(head->value);
			free(head->key);
			free(head);
			head = tmp;
			if (previous)
				previous->next = head;
			else
				*env = head;
			return ;
		}
		previous = head;
		head = head->next;		
	}
}

/*
 * Function: unset
 * ----------------------------
 *	Remove a variable from env
 */

int	unset(t_env *env, char *var)
{
	int		i;

	i = 0;
	if (!var)
		ft_printf_fd(2, "unset: not enough arguments\n");
	else if (!env_var_name_is_valid(var))
		ft_printf_fd(2, "unset: %s: invalid parameter name\n", var);
	else
	{
		remove_env_elem(&env, var);
		return (SUCCESS);
	}
	return (ERROR);
}
