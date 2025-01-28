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

static t_node_type token_to_node_type(t_token_type type)
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

static t_ast_node *create_command_from_token(t_token *token)
{
    char *args[1];
    
    args[0] = token->content;
    return create_command_node(args, 1);
}

// Find the last operator of given type in the token list
static t_token *find_last_operator(t_token *start, t_token *end, t_token_type type)
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

// Parse a sequence of tokens into an AST
static t_ast_node *parse_tokens_range(t_token *start, t_token *end)
{
    t_ast_node *node;
    t_token *operator;

    // Base case: single token
    if (start == end || !start)
    {
        if (!start)
            return NULL;
        return create_command_from_token(start);
    }

    // Look for OR first (lowest precedence)
    operator = find_last_operator(start, end, TOKEN_OR);
    if (!operator)
        operator = find_last_operator(start, end, TOKEN_AND); // Then look for AND
    if (!operator)
        operator = find_last_operator(start, end, TOKEN_PIPE); // Then look for PIPE

    // If no operator found, must be a single command
    if (!operator)
        return create_command_from_token(start);

    // Create operator node
    node = create_node(token_to_node_type(operator->type));
    if (!node)
        return NULL;

    if (operator->type == TOKEN_PIPE)
    {
        // Count commands in pipeline
        int cmd_count = 1;
        t_token *curr = start;
        t_ast_node **cmds;
        int i = 0;

        while (curr != end)
        {
            if (curr->type == TOKEN_PIPE)
                cmd_count++;
            curr = curr->next;
        }

        // Allocate command array
        cmds = malloc(sizeof(t_ast_node *) * cmd_count);
        if (!cmds)
        {
            free_ast(node);
            return NULL;
        }

        // Fill command array
        curr = start;
        while (curr != end)
        {
            if (curr->type == TOKEN_WORD)
            {
                cmds[i++] = create_command_from_token(curr);
                if (!cmds[i-1])
                {
                    while (--i >= 0)
                        free_ast(cmds[i]);
                    free(cmds);
                    free_ast(node);
                    return NULL;
                }
            }
            curr = curr->next;
        }

        node->pipeline = cmds;
        node->pipe_count = cmd_count;
    }
    else
    {
        // Recursively parse left and right sides
        node->left = parse_tokens_range(start, operator);
        node->right = parse_tokens_range(operator->next, end);

        if (!node->left || !node->right)
        {
            free_ast(node);
            return NULL;
        }
    }

    return node;
}

// Main parsing function
t_ast_node *parse_tokens(t_token *tokens)
{
    return parse_tokens_range(tokens, NULL);
}