/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:32:11 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/24 19:32:14 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_tree_node	*new_node(t_node_type type)
{
	t_tree_node	*node;

	if (type < 0)
	{
		printf("not implemented yet\n");
		exit(1);
	}
	node = malloc(sizeof(t_tree_node));
	if (!node)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
	node->cmd = NULL;
	node->type = type;
	return (node);
}

t_node_type	get_node_type(t_token_type token_type)
{
	if (token_type == TOKEN_AND)
		return (NODE_AND);
	if (token_type == TOKEN_OR)
		return (NODE_OR);
	if (token_type == TOKEN_PIPE)
		return (NODE_PIPE);
	if (token_type == TOKEN_WORD)
		return (NODE_COMMAND);
	if (token_type == TOKEN_IN)
		return (NODE_COMMAND);
	if (token_type == TOKEN_OUT)
		return (NODE_COMMAND);
	if (token_type == TOKEN_APPEND)
		return (NODE_COMMAND);
	if (token_type == TOKEN_HEREDOC)
		return (NODE_COMMAND);
	return (-1);
}
