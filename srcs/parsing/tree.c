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
	if (*token && (*token)->type == TOKEN_CLOSE_PAR)
		*token = (*token)->next;
	return (tmp_node);
}

t_tree_node	*update_tree_structure(t_tree_node *root, t_tree_node *tmp_node)
{
	if (!root)
		root = tmp_node;
	else if (root->left && !root->right)
		root->right = tmp_node;
	else
	{
		tmp_node->left = root;
		root = tmp_node;
	}
	return (root);
}

t_tree_node	*process_current_token(t_data *data, t_token **token,
		t_tree_node *root)
{
	t_tree_node	*tmp_node;

	if ((*token)->type == TOKEN_OPEN_PAR)
		return (handle_open_par(data, token, root));
	else if ((*token)->type == TOKEN_CLOSE_PAR)
		return (root);
	else if (token_is_part_of_command((*token)->type))
	{
		tmp_node = new_node(NODE_COMMAND);
		if (!tmp_node)
			return (free_tree(root), NULL);
		tmp_node->cmd = get_command(data, token);
		if (!tmp_node->cmd)
			return (free(tmp_node), free_tree(root), NULL);
		return (tmp_node);
	}
	else
	{
		tmp_node = new_node(get_node_type((*token)->type));
		if (tmp_node && *token)
			*token = (*token)->next;
		return (tmp_node);
	}
}

t_tree_node	*process_token(t_data *data, t_token **token, t_tree_node *root)
{
	t_tree_node	*tmp_node;

	if (!token || !*token)
		return (root);
	tmp_node = process_current_token(data, token, root);
	if (!tmp_node)
		return (NULL);
	return (update_tree_structure(root, tmp_node));
}

t_tree_node	*new_tree(t_data *data, t_token **token)
{
	t_tree_node	*root;

	root = NULL;
	if (!token || !(*token))
		return (NULL);
	while ((*token))
	{
		if ((*token)->type == TOKEN_CLOSE_PAR)
			break ;
		root = process_token(data, token, root);
		if (!root)
			return (NULL);
	}
	return (root);
}
