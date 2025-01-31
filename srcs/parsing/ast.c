/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:00:04 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/29 20:44:51 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "minishell.h"

/* Create a command node with given arguments */
t_ast_node  *ast_create_command(char **args, int arg_count)
{
    t_ast_node  *node;
    t_command   *cmd;

    node = create_node(NODE_COMMAND);
    if (!node)
        return (NULL);
    
    cmd = (t_command *)malloc(sizeof(t_command));
    if (!cmd)
    {
        free(node);
        return (NULL);
    }
    
    cmd->args = args;
    cmd->arg_count = arg_count;
    cmd->redirects = NULL;
    cmd->redir_count = 0;
    
    node->cmd = cmd;
    return (node);
}

/* Add a redirection to a command */
void    ast_add_redirection(t_command *cmd, t_redirection *redir)
{
    t_redirection   **new_redirects;
    
    new_redirects = (t_redirection **)malloc(
        sizeof(t_redirection *) * (cmd->redir_count + 1));
    if (!new_redirects)
        return ;
        
    if (cmd->redirects)
    {
        ft_memcpy(new_redirects, cmd->redirects, 
            sizeof(t_redirection *) * cmd->redir_count);
        free(cmd->redirects);
    }
    
    new_redirects[cmd->redir_count] = redir;
    cmd->redirects = new_redirects;
    cmd->redir_count++;
}
