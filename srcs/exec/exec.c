/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:27:57 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/13 19:17:25 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

static void	clear_waitlist(t_list **waitlist)
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
	int			child_count;
	t_exec		exec;
	int			i;

	if (!waitlist || !*waitlist)
		return ;
	child_count = ft_lstsize(*waitlist);
	init_exec(data, &exec, child_count);
	current = *waitlist;
	i = 0;
	while (current)
	{
		cmd = current->content;
		expand_args(data, cmd);
		if (!current->next && is_builtin(data, cmd))
			break ;
		data->status = exec_cmd(data, cmd, &exec, !(current->next));
		exec.child_pids[i++] = exec.pid;
		current = current->next;
	}
	data->exit_code = wait_child(exec.child_pids, child_count);
	free(exec.child_pids);
	clear_waitlist(waitlist);
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
		if (root->type == NODE_AND && data->status != 0)
			return ;
		if (root->type == NODE_OR && data->status == 0)
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
