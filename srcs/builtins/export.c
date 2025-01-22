/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 03:32:02 by maxweert          #+#    #+#             */
/*   Updated: 2025/01/22 16:11:28 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: ft_sorted_list_insert
 * ----------------------------
 *	Insert elem into env list and keep a sorted order.
 */

static void	ft_sorted_list_insert(t_env **begin_list, char *key, char *value)
{
	t_env	*head;
	t_env	*new;

	head = *begin_list;
	if (!head || ft_strcmp(head->key, key) >= 0)
	{
		*begin_list = env_create_elem(key, value);
		(*begin_list)->next = head;
		return ;
	}
	while (head)
	{
		if (head->next == 0 || ft_strcmp(head->next->key, key) >= 0)
		{
			new = env_create_elem(key, value);
			new->next = head->next;
			head->next = new;
			return ;
		}
		head = head->next;
	}
}

/*
 * Function: print_sorted_env
 * ----------------------------
 *	Create a sorted copy of env and print it. 
 *	Free and destroy the copy after printing it.
 */

static void	print_sorted_env(t_env *env)
{
	t_env	*sorted_env;
	sorted_env = NULL;
	while (env)
	{
		if (ft_strcmp(env->key, "_") != 0)
			ft_sorted_list_insert(&sorted_env, ft_strdup(env->key), ft_strdup(env->value));
		env = env->next;
	}
	while (sorted_env)
	{
		printf("declare -x %s=\"%s\"\n", sorted_env->key, sorted_env->value);
		sorted_env = sorted_env->next;
	}
	env_free(sorted_env);
}

/*
 * Function: env_var_is_valid
 * ----------------------------
 *	Check if a variable env is correctly formatted :
 *	Contains only ALPHANUM and _ and = characters.
 * 	Does NOT begin with a number.
 * 
 * 	Returns 1 if variable name is correct, otherwise 0.
 */

static int	env_var_is_valid(char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (0);
	i++;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_' && var[i] != '=')
			return (0);
		i++;
	}
	return (1);
}

/*
 * Function: ft_export
 * ----------------------------
 *	Add variables to env
 * 	If no args are provided, print env variables in sorted order
 * 	Return SUCCESS if nor error occured, otherwise ERROR
 */

int	ft_export(t_env *env, char **args)
{
	int	i;
	int	err;

	err = 0;
	i = 0;
	if (!args[0])
		print_sorted_env(env);
	while (args && args[i])
	{
		if (env_var_is_valid(args[i]) && ft_strchr(args[i], '='))
			env_add(&env, args[i]);
		else
		{
			err = 1;
			if (ft_isdigit(args[i][0]))
				ft_printf_fd(2, "export: not an identifier: %s\n", args[i]);
			else
				ft_printf_fd(2, "export: not valid in this context: %s\n",
					args[i]);
		}
		i++;
	}
	if (err)
		return (ERROR);
	return (SUCCESS);
}
