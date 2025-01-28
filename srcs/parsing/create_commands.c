/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:09:25 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/28 19:09:26 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"

t_ast_node *create_command_node(char **args, int arg_count)
{
    t_ast_node *node;
    t_command *cmd;
    int i;

    node = create_node(NODE_COMMAND);
    if (!node)
        return (NULL);

    cmd = malloc(sizeof(t_command));
    if (!cmd)
    {
        free(node);
        return (NULL);
    }

    cmd->args = malloc(sizeof(char *) * (arg_count + 1));
    if (!cmd->args)
    {
        free(cmd);
        free(node);
        return (NULL);
    }

    for (i = 0; i < arg_count; i++)
    {
        cmd->args[i] = strdup(args[i]);
        if (!cmd->args[i])
        {
            while (--i >= 0)
                free(cmd->args[i]);
            free(cmd->args);
            free(cmd);
            free(node);
            return (NULL);
        }
    }
    cmd->args[arg_count] = NULL;
    cmd->arg_count = arg_count;

    node->data = cmd;
    return (node);
}