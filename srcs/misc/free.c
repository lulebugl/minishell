/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:49:45 by maxweert          #+#    #+#             */
/*   Updated: 2025/01/27 15:20:26 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: free_data
 * ----------------------------
 *	Free all the data
 */

void	data_free(t_data *data)
{
	env_free(data->env);
	clear_tokens(&data->tokens);
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

void clear_tokens(t_token **tokens)
{
	if (tokens && *tokens)
	{
		if ((*tokens)->next)
			clear_tokens(&(*tokens)->next);
		free((*tokens)->content);
		free(*tokens);
		*tokens = NULL;
	}
}
