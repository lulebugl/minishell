/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:49:45 by maxweert          #+#    #+#             */
/*   Updated: 2025/01/31 17:34:55 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"

/*
 * Function: free_data
 * ----------------------------
 *	Free all the data
 */

void	data_free(t_data *data)
{
	env_free(data->env);
	clear_tokens(&data->tokens);
	free_tree(data->ast);
	data->ast = NULL;
}

void	clear_tokens(t_token **tokens)
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

void	free_str_arr(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}
