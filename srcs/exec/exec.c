/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:27:57 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/04 16:35:43 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

int		expander_new(t_data *data, char **argv, int ac);
void	wait_child(t_data *data, pid_t *child_pids, int child_count);
void	init_exec(t_data *data, t_exec *exec, int child_count);

void	expand_args(t_data *data, t_command *cmd)
{
	char	**av;

	av = cmd->args;
	if (expander_new(data, av, cmd->arg_count))
		// probably a lot of leaks,	will need to rewrite it i think
		err_and_exit(data);
}

int	exec_cmd(t_data *data, t_command *cmd, t_exec *exec, t_list *curr)
{
	int	pipe_err[2];

	if (!cmd)
		return (1);
	exec->pipe[0] = -1;
	exec->pipe[1] = -1;
	if (!data->envp)
		err_and_exit(data);
	if (curr->next)
	{
		if (pipe(exec->pipe) == -1)
			err_and_exit(data);
		exec->fd_out = exec->pipe[1];
	}
	else
	{
		// Last command outputs to stdout
		exec->fd_out = STDOUT_FILENO;
	}
	exec->pid = fork();
	if (exec->pid == -1)
		err_and_exit(data);
	if (exec->pid != 0)
		init_signals();
	if (exec->pid == 0)
		child_process(data, cmd, exec);
	else
		parent_process(exec);
	debug_cmd(data, cmd);
	return (0);
}

void	execute_waitlist(t_list **waitlist, t_data *data)
{
	t_list		*current;
	t_command	*cmd;
	int			child_count;
	t_exec		exec;
	int			i;

	if (!waitlist || !*waitlist)
		return ;
	if (data->exec_debug)
		printf("-- starting executing waitlist --\n");
	child_count = ft_lstsize(*waitlist);
	init_exec(data, &exec, child_count);
	current = *waitlist;
	i = 0;
	while (current)
	{
		cmd = current->content;
		expand_args(data, cmd);
		data->status = exec_cmd(data, cmd, &exec, current);
		exec.child_pids[i++] = exec.pid;
		current = current->next;
	}
	wait_child(data, exec.child_pids, child_count);
	ft_lstclear(waitlist, NULL);
	*waitlist = NULL;
	if (data->exec_debug)
		printf("-- done executing --\n");
}

void	execute_ast(t_data *data, t_tree_node *root, t_tree_node *previous,
		t_list **waitlist)
{
	if (!root)
		return ;
	execute_ast(data, root->left, root, waitlist);
	// Print current state
	if (data->exec_debug)
		printf("\nCurrent node: ");
	if (root->type == NODE_COMMAND && root->cmd)
	{
		if (data->exec_debug)
			printf("COMMAND: ");
		if (data->exec_debug)
			for (int i = 0; i < root->cmd->arg_count; i++)
				printf("%s ", root->cmd->args[i]);
		if (data->exec_debug)
			printf("\n");
	}
	else if (root->type == NODE_AND)
	{
		if (data->exec_debug)
			printf("AND\n");
	}
	else if (root->type == NODE_OR)
		if (data->exec_debug)
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
		if (data->exec_debug)
			printf("Adding command to waitlist\n");
		ft_lstadd_back(waitlist, ft_lstnew(root->cmd));
	}
	else if (root->type == NODE_AND || root->type == NODE_OR)
	{
		printf("Logical operator found, executing current waitlist\n");
		execute_waitlist(waitlist, data);
	}
	execute_ast(data, root->right, root, waitlist);
}

void	execute_ast_debug(t_data *data, t_tree_node *root,
		t_tree_node *previous, t_list **waitlist);

int	exec(t_data *data)
{
	t_tree_node	*root;
	t_list		*waitlist;

	root = data->ast;
	waitlist = NULL;
	execute_ast(data, data->ast, NULL, &waitlist);	
	if (waitlist)
		execute_waitlist(&waitlist, data);
	return (0);
}

