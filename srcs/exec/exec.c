/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:27:57 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/20 19:52:14 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(t_data *data, t_command *cmd, t_exec *exec, bool last)
{
	if (!cmd || !cmd->arg_lst)
		return (1);
	if (!last && pipe(exec->pipe) == -1)
	{
		cleanup_exec(exec);
		err_and_exit(data);
	}
	exec->pid = fork();
	if (exec->pid < 0)
	{
		if (!last && !close(exec->pipe[0]))
			close(exec->pipe[1]);
		cleanup_exec(exec);
		err_and_exit(data);
	}
	if (exec->pid == 0)
		child_process(data, cmd, exec, last);
	else
		parent_process(exec, last);
	return (0);
}

void	clear_waitlist(t_list **waitlist)
{
	if (waitlist && *waitlist)
	{
		if ((*waitlist)->next)
			clear_waitlist(&(*waitlist)->next);
		free(*waitlist);
		*waitlist = NULL;
	}
}

void	execute_waitlist(t_list **waitlist, t_data *data)
{
	t_list		*current;
	t_command	*cmd;
	t_exec		exec;
	int			i;

	if (!waitlist || !*waitlist)
		return ;
	current = *waitlist;
	i = 0;
	init_exec(data, &exec, waitlist);
	if (!current->next && is_builtin(current->content))
		return (exec_single_builtin(data, current->content, &exec));
	while (current)
	{
		cmd = current->content;
		if (expander(data, cmd) == ERROR)
			return (data->exit_code = wait_child(&exec), cleanup_exec(&exec));
		data->exit_code = exec_cmd(data, cmd, &exec, !(current->next));
		exec.child_pids[exec.child_count++] = exec.pid;
		current = current->next;
	}
	data->exit_code = wait_child(&exec);
	cleanup_exec(&exec);
}

void	execute_ast(t_data *data, t_tree_node *root, t_list **waitlist)
{
	if (!root)
		return ;
	execute_ast(data, root->left, waitlist);
	if (root->type == NODE_COMMAND)
		ft_lstadd_back(waitlist, ft_lstnew(root->cmd));
	else if (root->type == NODE_AND || root->type == NODE_OR)
	{
		execute_waitlist(waitlist, data);
		if (root->type == NODE_AND && data->exit_code != 0)
			return ;
		if (root->type == NODE_OR && data->exit_code == 0)
			return ;
	}
	execute_ast(data, root->right, waitlist);
}

int	exec(t_data *data)
{
	t_tree_node	*root;
	t_list		*waitlist;

	root = data->ast;
	waitlist = NULL;
	execute_ast(data, data->ast, &waitlist);
	if (waitlist)
		execute_waitlist(&waitlist, data);
	return (0);
}
