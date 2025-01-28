/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:03:39 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/28 19:03:40 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"

t_token *find_last_operator(t_token *start, t_token *end, t_token_type type)
{
    t_token *last = NULL;
    t_token *current = start;

    while (current != end)
    {
        if (current->type == type)
            last = current;
        current = current->next;
    }
    return last;
}

t_node_type token_to_node_type(t_token_type type)
{
    if (type == TOKEN_PIPE)
        return NODE_PIPELINE;
    else if (type == TOKEN_WORD)
        return NODE_COMMAND;
    else if (type == TOKEN_AND)
        return NODE_AND;
    else if (type == TOKEN_OR)
        return NODE_OR;
    return NODE_COMMAND;
}

/*
** Create an ast node based on its type
** Returns the node if successful, else NULL
*/

t_ast_node *create_node(t_node_type type)
{
    t_ast_node *node;

    node = malloc(sizeof(t_ast_node));
    if (!node)
        return (NULL);
    node->type = type;
    node->left = NULL;
    node->pipeline = NULL;
    node->pipe_count = 0;
    node->right = NULL;
    node->cmd = NULL;
    return (node);
}

void free_ast(t_ast_node *node)
{
    if (!node)
        return;

    if (node->type == NODE_COMMAND)
    {
        t_command *cmd = node->cmd;
        for (int i = 0; i < cmd->arg_count; i++)
            free(cmd->args[i]);
        free(cmd->args);
        free(cmd);
    }
    else if (node->type == NODE_PIPELINE)
    {
        for (int i = 0; i < node->pipe_count; i++)
            free_ast(node->pipeline[i]);
        free(node->pipeline);
    }
    else // AND/OR
    {
        free_ast(node->left);
        free_ast(node->right);
    }
    free(node);
}
