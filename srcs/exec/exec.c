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

void	wait_child(t_data *data, pid_t *child_pids, int child_count)
{
	int	i;
	int	status;

	i = 0;
	while (i < child_count)
	{
		waitpid(child_pids[i], &status, 0);
		if (WIFEXITED(status))
			data->status = WEXITSTATUS(status);
		i++;
	}
}

void	init_exec(t_data *data, t_exec *exec, int child_count)
{
	ft_memset(exec, 0, sizeof(t_exec));
	exec->child_pids = malloc(sizeof(pid_t) * child_count);
	if (!exec->child_pids)
		err_and_exit(data);
}

int		expander_new(t_data *data, char **argv, int ac);

int	exec_cmd(t_data *data, t_command *cmd, t_exec *exec)
{
	int	i;

	i = -1;
	if (!cmd)
		return (1);
	// cmd->args = expander_new(data, cmd->args, cmd->arg_count);
	// if (!cmd->args)
	// 	err_and_exit(data);
	if (expander_new(data, cmd->args, cmd->arg_count))
		err_and_exit(data);
	while (++i < cmd->arg_count)
		printf(" [%s]",cmd->args[i]);
	printf("\n");
	return (0);
}

void	execute_waitlist(t_list **waitlist, t_data *data)
{
	t_list		*current;
	t_command	*cmd;
	int			child_count;
	t_exec		exec;

	if (!waitlist || !*waitlist)
		return ;
	printf("-- starting executing waitlist --\n");
	child_count = ft_lstsize(*waitlist);
	init_exec(data, &exec, child_count);
	current = *waitlist;
	while (current)
	{
		cmd = current->content;
		data->status = exec_cmd(data, cmd, &exec);
		current = current->next;
	}
	// wait_child(data, exec.child_pids, child_count);
	ft_lstclear(waitlist, NULL);
	*waitlist = NULL;
	printf("-- done executing --\n");
}

void	execute_ast(t_data *data, t_tree_node *root, t_tree_node *previous,
		t_list **waitlist)
{
	if (!root)
		return ;
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
	if (previous)
	{
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
		printf("Added\n");
	}
	else if (root->type == NODE_AND || root->type == NODE_OR)
	{
		printf("Logical operator found, executing current waitlist\n");
		execute_waitlist(waitlist, data);
	}
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
		printf("final commands\n");
		execute_waitlist(&waitlist, data);
		printf("executed\n");
	}
	return (0);
}

