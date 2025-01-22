/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 03:32:02 by maxweert          #+#    #+#             */
/*   Updated: 2025/01/22 12:30:46 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!args || !args[0])
		ft_env(env);
	while (args[i])
	{
		if (env_var_is_valid(args[i]) && ft_strchr(args[i], '='))
			add_env(&env, args[i]);
		else
		{
			err = 1;
			if (ft_isdigit(args[i][0]))
				ft_printf_fd(2, "export: not an identifier: %s\n", args[i]);
			else
				ft_printf_fd(2, "export: not valid in this context: %s\n", args[i]);
		}
		i++;
	}
	if (err)
		return (ERROR);
	return (SUCCESS);
}
