/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:31:41 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/01 18:31:42 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "ast.h"

static void	execute_waitlist_debug(t_list **waitlist)
{
	t_list		*current;
	t_command	*cmd;

	current = *waitlist;
	printf("Executing waitlist:\n");
	while (current)
	{
		cmd = current->content;
		printf("Would execute: ");
		for (int i = 0; i < cmd->arg_count; i++)
			printf("%s ", cmd->args[i]);
		printf("\n");
		current = current->next;
	}
	ft_lstclear(waitlist, NULL);
	*waitlist = NULL; // Important: set to NULL after clearing
}

void	execute_ast_debug(t_data *data, t_tree_node *root, t_tree_node *previous,
		t_list **waitlist)
{
	if (!root)
		return ;
	execute_ast_debug(data, root->left, root, waitlist);
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
		// printf("Previous status: %d\n", data->status);
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
	if (root->type == NODE_COMMAND)
	{
		printf("Adding command to waitlist\n");
		ft_lstadd_back(waitlist, ft_lstnew(root->cmd));
	}
	else if (root->type == NODE_AND || root->type == NODE_OR)
	{
		printf("Logical operator found, executing current waitlist\n");
		execute_waitlist_debug(waitlist);
	}
	// Process right child
	execute_ast_debug(data, root->right, root, waitlist);
}

int	exec_debug(t_data *data)
{
	t_tree_node	*root;
	t_list		*waitlist;

	root = data->ast;
	waitlist = NULL;
	execute_ast_debug(data, data->ast, NULL, &waitlist);
	if (waitlist)
		execute_waitlist_debug(&waitlist);
	return (0);
}

