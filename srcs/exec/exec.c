/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:27:57 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/31 17:27:58 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exec.h"
#include "minishell.h"

static void execute_waitlist(t_list **waitlist)
{
    t_list *current = *waitlist;
    printf("Executing waitlist:\n");
    while (current)
    {
        t_command *cmd = current->content;
        printf("Would execute: ");
        for (int i = 0; i < cmd->arg_count; i++)
            printf("%s ", cmd->args[i]);
        printf("\n");
        current = current->next;
    }
    ft_lstclear(waitlist, NULL);
    *waitlist = NULL;  // Important: set to NULL after clearing
}

void execute_ast(t_data *data, t_tree_node *root, t_tree_node *previous, t_list **waitlist)
{
    // Base case
    if (!root)
    {
        // if (waitlist)  // Execute any remaining commands in waitlist
        // {
        //    printf("End of branch, executing remaining waitlist\n");
        //     execute_waitlist(&waitlist);
        // }
        return ;
    }

    // Process left child
    execute_ast(data, root->left, root, waitlist);

    // Print current state
    printf("\nCurrent node: ");
    if (root->type == NODE_COMMAND && root->cmd)
    {
        printf("COMMAND: ");
        for (int i = 0; i < root->cmd->arg_count; i++)
            printf("%s ", root->cmd->args[i]);
        printf("\n");
    }
    else if (root->type == NODE_AND)
        printf("AND\n");
    else if (root->type == NODE_OR)
        printf("OR\n");

    // Handle logical operators
    if (previous)
    {
        //printf("Previous status: %d\n", data->status);
        if (previous->type == NODE_AND && data->status != 0)
        {
            printf("AND condition failed, clearing waitlist\n");
            ft_lstclear(waitlist, NULL);
        }
        else if (previous->type == NODE_OR && data->status == 0)
        {
            printf("OR condition succeeded, clearing waitlist\n");
            ft_lstclear(waitlist, NULL);
        }
    }

    // Handle current node
    if (root->type == NODE_COMMAND)
    {
        printf("Adding command to waitlist\n");
        ft_lstadd_back(waitlist, ft_lstnew(root->cmd));
        
        // If this is a leaf node (no more logical operators ahead), execute waitlist
        // if (!root->right && !root->left)
        // {
        //     printf("Leaf command node, executing waitlist\n");
        //     execute_waitlist(&waitlist);
        // }
    }
    else if (root->type == NODE_AND || root->type == NODE_OR)
    {
        printf("Logical operator found, executing current waitlist\n");
        execute_waitlist(waitlist);
    }

    // Process right child
    execute_ast(data, root->right, root, waitlist);
}

int	exec(t_data *data)
{
	t_tree_node	*root;
	t_list		*waitlist;

	root = data->ast;
	waitlist = NULL;
	execute_ast(data, data->ast, NULL, &waitlist);
	if (waitlist)
		{
			// printf("test\n");
			execute_waitlist(&waitlist);
		}
	return (0);
}

