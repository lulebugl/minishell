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

/* ast.c */
#include "ast.h"

static t_ast_node *create_node(t_node_type type, void *data)
{
    t_ast_node *node;

    node = malloc(sizeof(t_ast_node));
    if (!node)
        return (NULL);
    node->type = type;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

// Count number of word tokens until a pipe or end
static int count_command_words(t_token *token)
{
    int count;

    count = 0;
    while (token && token->type == TOKEN_WORD)
    {
        count++;
        token = token->next;
    }
    return (count);
}

// Build a command node from tokens
static t_ast_node *build_command(t_token **tokens)
{
    t_command   *cmd;
    t_ast_node  *node;
    int         i;
    int         word_count;

    // Count words in this command
    word_count = count_command_words(*tokens);
    if (word_count == 0)
        return (NULL);

    // Allocate command structure
    cmd = malloc(sizeof(t_command));
    if (!cmd)
        return (NULL);
    cmd->args = malloc(sizeof(char *) * (word_count + 1));
    if (!cmd->args)
    {
        free(cmd);
        return (NULL);
    }
    cmd->arg_count = word_count;

    // Copy command and arguments
    i = 0;
    while (i < word_count)
    {
        cmd->args[i] = ft_strdup((*tokens)->content);
        *tokens = (*tokens)->next;
        i++;
    }
    cmd->args[i] = NULL;  // NULL terminate the array

    // Create the AST node
    node = create_node(NODE_COMMAND, cmd);
    if (!node)
    {
        // Free everything if node creation failed
        for (i = 0; i < word_count; i++)
            free(cmd->args[i]);
        free(cmd->args);
        free(cmd);
        return (NULL);
    }
    return (node);
}

// Main function to build the AST
t_ast_node *build_ast(t_token *tokens)
{
    t_ast_node  *left;
    t_ast_node  *pipe_node;

    if (!tokens)
        return (NULL);

    // Build the first command
    left = build_command(&tokens);
    if (!left)
        return (NULL);

    // If there's a pipe, continue building
    while (tokens && tokens->type == TOKEN_PIPE)
    {
        // Create a pipe node
        pipe_node = create_node(NODE_PIPE, NULL);
        if (!pipe_node)
        {
            free_ast(left);
            return (NULL);
        }

        // Skip the pipe token
        tokens = tokens->next;

        // Set the left child to our previous command/pipe
        pipe_node->left = left;

        // Build the right command
        pipe_node->right = build_command(&tokens);
        if (!pipe_node->right)
        {
            free_ast(pipe_node);
            return (NULL);
        }

        // Update left for the next iteration
        left = pipe_node;
    }

    return (left);
}

// Print the AST with indentation for visualization
void print_ast(t_ast_node *node, int level)
{
    int i;

    if (!node)
        return;

    // Print indentation
    for (i = 0; i < level; i++)
        printf("  ");

    // Print node content
    if (node->type == NODE_PIPE)
    {
        printf("PIPE\n");
    }
    else if (node->type == NODE_COMMAND)
    {
        t_command *cmd = (t_command *)node->data;
        printf("COMMAND: ");
        for (i = 0; i < cmd->arg_count; i++)
        {
            printf("%s", cmd->args[i]);
            if (i < cmd->arg_count - 1)
                printf(" ");
        }
        printf("\n");
    }

    // Print children
    if (node->left)
        print_ast(node->left, level + 1);
    if (node->right)
        print_ast(node->right, level + 1);
}

void free_ast(t_ast_node *node)
{
    if (!node)
        return;

    // Free children first
    free_ast(node->left);
    free_ast(node->right);

    // Free command data if this is a command node
    if (node->type == NODE_COMMAND)
    {
        t_command *cmd = (t_command *)node->data;
        for (int i = 0; i < cmd->arg_count; i++)
            free(cmd->args[i]);
        free(cmd->args);
        free(cmd);
    }

    // Free the node itself
    free(node);
}