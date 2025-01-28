/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:03:30 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/28 19:03:32 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"

static void print_command(t_command *cmd, int level)
{
    for (int i = 0; i < level; i++)
        printf("  ");
    printf("CMD: ");
    for (int i = 0; i < cmd->arg_count; i++)
    {
        printf("%s", cmd->args[i]);
        if (i < cmd->arg_count - 1)
            printf(" ");
    }
    printf("\n");
}

void print_ast(t_ast_node *node, int level)
{
    if (!node)
        return;

    for (int i = 0; i < level; i++)
        printf("  ");

    switch (node->type)
    {
        case NODE_COMMAND:
            print_command(node->data, 0);
            break;
        case NODE_PIPELINE:
            printf("PIPELINE:\n");
            for (int i = 0; i < node->pipe_count; i++)
                print_ast(node->pipeline[i], level + 1);
            break;
        case NODE_AND:
            printf("AND\n");
            print_ast(node->left, level + 1);
            print_ast(node->right, level + 1);
            break;
        case NODE_OR:
            printf("OR\n");
            print_ast(node->left, level + 1);
            print_ast(node->right, level + 1);
            break;
    }
}