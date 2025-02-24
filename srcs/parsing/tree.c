/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:31:11 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/19 16:18:09 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree_node	*handle_open_par(t_data *data, t_token **token, t_tree_node *root)
{
	t_tree_node	*tmp_node;

	*token = (*token)->next;
	tmp_node = new_tree(data, token);
	if (!tmp_node)
		return (free_tree(root), NULL);
	return (tmp_node);
}

t_tree_node	*handle_command(t_data *data, t_token **token, t_tree_node *root)
{
	t_tree_node	*tmp_node;

	tmp_node = new_node(NODE_COMMAND);
	if (!tmp_node)
		return (free_tree(root), NULL);
	tmp_node->cmd = get_command(data, token);
	if (!tmp_node->cmd)
		return (free(tmp_node), free_tree(root), NULL);
	return (tmp_node);
}

t_tree_node	*handle_other_nodes(t_token **token)
{
	return (new_node(get_node_type((*token)->type)));
}

t_tree_node	*process_token(t_data *data, t_token **token, t_tree_node *root)
{
	t_tree_node	*tmp_node;

	tmp_node = NULL;
	if ((*token)->type == TOKEN_OPEN_PAR)
		tmp_node = handle_open_par(data, token, root);
	else if ((*token)->type == TOKEN_CLOSE_PAR)
		return (root);
	else if (token_is_part_of_command((*token)->type))
		tmp_node = handle_command(data, token, root);
	else
		tmp_node = handle_other_nodes(token);
	if (!tmp_node)
		return (NULL);
	if (!root)
		root = tmp_node;
	else if (root->left && !root->right)
		root->right = tmp_node;
	else
	{
		tmp_node->left = root;
		root = tmp_node;
	}
	if ((*token) && tmp_node->type != NODE_COMMAND)
		(*token) = (*token)->next;
	return (root);
}

t_tree_node	*new_tree(t_data *data, t_token **token)
{
	t_tree_node	*root;

	root = NULL;
	if (!(*token))
		return (NULL);
	while ((*token))
	{
		root = process_token(data, token, root);
		if (!root)
			return (NULL);
	}
	return (root);
}
