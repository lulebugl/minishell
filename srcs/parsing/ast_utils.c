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

t_ast_node *create_pipeline_node(t_ast_node **commands, int cmd_count)
{
    t_ast_node *node;

    node = create_node(NODE_PIPELINE);
    if (!node)
        return (NULL);

    node->pipeline = malloc(sizeof(t_ast_node *) * cmd_count);
    if (!node->pipeline)
    {
        free(node);
        return (NULL);
    }

    for (int i = 0; i < cmd_count; i++)
        node->pipeline[i] = commands[i];
    node->pipe_count = cmd_count;

    return (node);
}

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
    node->data = NULL;
    return (node);
}

void free_ast(t_ast_node *node)
{
    if (!node)
        return;

    if (node->type == NODE_COMMAND)
    {
        t_command *cmd = node->data;
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
