/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:00:04 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/27 20:00:05 by llebugle         ###   ########.fr       */
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

// Parse a sequence of tokens into an AST
// static t_ast_node *parse_tokens_range(t_token *start, t_token *end)
// {
//     t_ast_node *node;
//     t_token *operator;

//     // Base case: single token
//     if (start == end || !start)
//     {
//         if (!start)
//             return NULL;
//         return create_command_from_token(start);
//     }

//     // Look for OR first (lowest precedence)
//     operator = find_last_operator(start, end, TOKEN_OR);
//     if (!operator)
//         operator = find_last_operator(start, end, TOKEN_AND); // Then look for AND
//     if (!operator)
//         operator = find_last_operator(start, end, TOKEN_PIPE); // Then look for PIPE

//     // If no operator found, must be a single command
//     if (!operator)
//         return create_command_from_token(start);

//     // Create operator node
//     node = create_node(token_to_node_type(operator->type));
//     if (!node)
//         return NULL;

//     if (operator->type == TOKEN_PIPE)
//     {
//         // Count commands in pipeline
//         int cmd_count = 1;
//         t_token *curr = start;
//         t_ast_node **cmds;
//         int i = 0;

//         while (curr != end)
//         {
//             if (curr->type == TOKEN_PIPE)
//                 cmd_count++;
//             curr = curr->next;
//         }

//         // Allocate command array
//         cmds = malloc(sizeof(t_ast_node *) * cmd_count);
//         if (!cmds)
//         {
//             free_ast(node);
//             return NULL;
//         }

//         // Fill command array
//         curr = start;
//         while (curr != end)
//         {
//             if (curr->type == TOKEN_WORD)
//             {
//                 cmds[i++] = create_command_from_token(curr);
//                 if (!cmds[i-1])
//                 {
//                     while (--i >= 0)
//                         free_ast(cmds[i]);
//                     free(cmds);
//                     free_ast(node);
//                     return NULL;
//                 }
//             }
//             curr = curr->next;
//         }

//         node->pipeline = cmds;
//         node->pipe_count = cmd_count;
//     }
//     else
//     {
//         // Recursively parse left and right sides
//         node->left = parse_tokens_range(start, operator);
//         node->right = parse_tokens_range(operator->next, end);

//         if (!node->left || !node->right)
//         {
//             free_ast(node);
//             return NULL;
//         }
//     }

//     return node;
// }

