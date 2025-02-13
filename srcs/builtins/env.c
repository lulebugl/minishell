/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:06:44 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/13 20:54:21 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: ft_env
 * ----------------------------
 *	Print all the environment variables.
 * 	Returns SUCCESS
 */

int	ft_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (SUCCESS);
}
