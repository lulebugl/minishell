/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:49:45 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/18 19:06:45 by maxweert         ###   ########.fr       */
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
	if (data)
	{
		env_free(data->env);
		data->env = NULL;
		clear_tokens(&data->tokens);
		free_tree(data->ast);
		data->ast = NULL;
		if (data->rl)
			free(data->rl);
	}
}

void	reset_data(t_data *data)
{
	if (data)
	{
		clear_tokens(&data->tokens);
		free_tree(data->ast);
		if (data->rl)
			free(data->rl);
		data->rl = NULL;
		data->ast = NULL;
	}
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
	if (!strs || *strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	free_tree(t_tree_node *root)
{
	if (!root)
		return ;
	if (root->type == NODE_COMMAND)
		free_command(root->cmd);
	free_tree(root->left);
	free_tree(root->right);
	free(root);
}
