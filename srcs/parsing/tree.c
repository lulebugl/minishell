/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:31:11 by maxweert          #+#    #+#             */
/*   Updated: 2025/01/30 23:32:46 by maxweert         ###   ########.fr       */
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

t_tree_node	*new_tree(t_data *data, t_token **token)
{
	t_tree_node	*root;
	t_tree_node	*tmp_node;
	t_command	*command;
	t_token		*token_head;

	token_head = *token;
	root = NULL;
	tmp_node = NULL;
	if (!(*token))
		return (NULL);
	while ((*token))
	{
		if ((*token)->type == TOKEN_AND)
			tmp_node = new_node(NODE_AND);
		else if ((*token)->type == TOKEN_OR)
			tmp_node = new_node(NODE_OR);
		else if ((*token)->type == TOKEN_PIPE)
			tmp_node = new_node(NODE_PIPE);
		if ((*token)->type == TOKEN_OPEN_PAR)
		{
			*token = (*token)->next;
			tmp_node = new_tree(data, token);
		}
		else if ((*token)->type == TOKEN_CLOSE_PAR)
			return (root);
		else if ((*token)->type == TOKEN_WORD)
		{
			tmp_node = new_node(NODE_COMMAND);
			tmp_node->cmd = get_command(token);
			while ((*token) && ((*token)->type != TOKEN_AND && (*token)->type != TOKEN_OR
				&& (*token)->type != TOKEN_PIPE && (*token)->type != TOKEN_OPEN_PAR && (*token)->type != TOKEN_CLOSE_PAR))
				(*token) = (*token)->next;
		}
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
