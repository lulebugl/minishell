/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:31:11 by maxweert          #+#    #+#             */
/*   Updated: 2025/01/31 00:09:25 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"

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

static t_tree_node	*new_node(t_node_type type)
{
	t_tree_node	*node;

	node = malloc(sizeof(t_tree_node));
	if (!node)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
	node->cmd = NULL;
	node->type = type;
	return (node);
}

static t_node_type	get_node_type(t_token_type token_type)
{
	if (token_type == TOKEN_AND)
		return (NODE_AND);
	if (token_type == TOKEN_OR)
		return (NODE_OR);
	if (token_type == TOKEN_PIPE)
		return (NODE_PIPE);
	return (NODE_COMMAND);
}

t_tree_node	*new_tree(t_data *data, t_token **token)
{
	t_tree_node	*root;
	t_tree_node	*tmp_node;

	root = NULL;
	tmp_node = NULL;
	if (!(*token))
		return (NULL);
	while ((*token))
	{
		if ((*token)->type == TOKEN_OPEN_PAR)
		{
			*token = (*token)->next;
			tmp_node = new_tree(data, token);
		}
		else if ((*token)->type == TOKEN_CLOSE_PAR)
			return (root);
		else if ((*token)->type == TOKEN_WORD)
		{
			tmp_node = new_node(get_node_type((*token)->type));
			//rajouter protect
			tmp_node->cmd = get_command(token);
		}
		else
			tmp_node = new_node(get_node_type((*token)->type));
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
	}
	return (root);
}
