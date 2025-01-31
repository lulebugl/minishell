/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:42:23 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/29 20:45:16 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "minishell.h"

t_ast_node			*create_command(t_token *token);

t_ast_node  *create_pipeline_node(t_token *start, t_token *end)
{
    t_ast_node  *node;
    t_token     *curr;
    t_ast_node  **cmds;
    int         cmd_count;
    int         i;

    //printf("\n=== Starting create_pipeline_node ===\n");
    // Count commands in pipeline
    cmd_count = 1;
    curr = start;
    while (curr != end && curr)
    {
        if (curr->type == TOKEN_PIPE)
            cmd_count++;
        curr = curr->next;
    }
    //printf("Found %d commands in pipeline\n", cmd_count);
    
    cmds = malloc(sizeof(t_ast_node *) * cmd_count);
    if (!cmds)
        return (NULL);
    
    // Fill commands array
    //printf("\nFilling commands array:\n");
    i = 0;
    curr = start;
    while (curr != end && curr && i < cmd_count)
    {
        // Skip non-word tokens at start of command
        while (curr && curr->type != TOKEN_WORD && curr->type != TOKEN_PIPE)
            curr = curr->next;
        
        if (curr && curr->type == TOKEN_WORD)
        {
            //printf("Creating command %d from token: '%s'\n", i, curr->content);
            cmds[i] = create_command(curr);
            if (!cmds[i])
            {
                //printf("Failed to create command %d\n", i);
                while (--i >= 0)
                    free_ast(cmds[i]);
                return (free(cmds), NULL);
            }
            i++;
            
            // Skip to next pipe
            while (curr && curr->type != TOKEN_PIPE)
                curr = curr->next;
            // Skip the pipe token
            if (curr)
                curr = curr->next;
        }
    }
    
    // Verify we created the expected number of commands
    if (i != cmd_count)
    {
        //printf("Error: Expected %d commands but created %d\n", cmd_count, i);
        while (--i >= 0)
            free_ast(cmds[i]);
        return (free(cmds), NULL);
    }

    node = create_node(NODE_PIPE);
    if (!node)
    {
        while (--i >= 0)
            free_ast(cmds[i]);
        return (free(cmds), NULL);
    }

    node->pipeline = cmds;
    node->pipe_count = cmd_count;
    node->left = NULL;
    node->right = NULL;
    node->cmd = NULL;
    return (node);
}

/* Handle logical operator node creation */
static t_ast_node	*create_operator_node(t_token *start, t_token *operator,
		t_token * end, t_data *data)
{
	t_ast_node	*node;

	node = create_node(token_to_node_type(operator->type));
	if (!node)
		return (NULL);
	node->left = parse_tokens_r(data, start, operator);
	if (!node->left)
	{
		free_ast(node);
		return (NULL);
	}
	node->right = parse_tokens_r(data, operator->next, end);
	if (!node->right)
	{
		free_ast(node);
		return (NULL);
	}
	return (node);
}

/* Find operator with specified precedence */
static t_token	*find_operator_by_precedence(t_token *start, t_token *end)
{
	t_token	*operator;

	operator= find_last_operator(start, end, TOKEN_OR);
	if (!operator)
		operator= find_last_operator(start, end, TOKEN_AND);
	if (!operator)
		operator= find_last_operator(start, end, TOKEN_PIPE);
	//printf("last operator : %s", operator->content);
	return (operator);
}

t_ast_node	*parse_tokens_r(t_data *data, t_token *start, t_token *end)
{
	t_token		*operator;
	t_ast_node	*node;

	if (!start || start == end)
	{
		if (!start)
			return (NULL);
		return (create_command(start));
	}
	operator= find_operator_by_precedence(start, end);
	if (!operator)
		return (create_command(start));
	if (operator->type == TOKEN_PIPE)
		node = create_pipeline_node(start, end);
	else
		node = create_operator_node(start, operator, end, data);
	return (node);
}

/* Main parsing function */
t_ast_node	*parse_tokens(t_data *data, t_token *tokens)
{
	return (parse_tokens_r(data, tokens, NULL));
}