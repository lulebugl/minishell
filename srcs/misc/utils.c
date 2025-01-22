/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 03:33:49 by maxweert          #+#    #+#             */
/*   Updated: 2025/01/22 03:34:00 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: env_var_name_is_valid
 * ----------------------------
 *	Check if the name of a variable env is correctly formatted :
 *	Contains only ALPHANUM and _ characters.
 * 	Does NOT begin with a number.
 * 
 * 	Returns 1 if variable name is correct, otherwise 0.
 */

int	env_var_name_is_valid(char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (0);
	i++;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
