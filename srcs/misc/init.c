/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:45:59 by maxweert          #+#    #+#             */
/*   Updated: 2025/01/29 00:54:33 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: init_data
 * ----------------------------
 *	Initialize the data structure variables.
 */

void	data_init(t_data *data)
{
	data->status = 0;	
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
		env_add_key(env, env_key_from_str(env_arr[i]),
			env_value_from_str(env_arr[i]));
		i++;
	}
}


void	init_signals(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sigint_handler;
	sigaction(SIGINT, &act, NULL);
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}
