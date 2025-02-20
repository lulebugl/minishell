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
	if (!last)
		if (pipe(exec->pipe) == -1)
			err_and_exit(data);
	exec->pid = fork();
	if (exec->pid < 0)
		err_and_exit(data);
	if (exec->pid == 0)
		child_process(data, cmd, exec, last);
	else
	{
		if (exec->fd_in != STDIN_FILENO)
			close(exec->fd_in);
		if (!last)
		{
			close(exec->pipe[1]);
			exec->fd_in = exec->pipe[0];
		}
		exec->child_pids[exec->id++] = exec->pid;
	}
	debug_cmd(data, cmd); // remove at the end
	return (0);
}

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

void	restore_fd(t_data *data)
{
	// Restore original stdin if it was saved
	if (data->saved_stdin != -1)
	{
		dup2(data->saved_stdin, STDIN_FILENO);
		close(data->saved_stdin);
		data->saved_stdin = -1;
	}
	// Restore original stdout if it was saved
	if (data->saved_stdout != -1)
	{
		dup2(data->saved_stdout, STDOUT_FILENO);
		close(data->saved_stdout);
		data->saved_stdout = -1;
	}
}

void	exec_single_builtin(t_data *data, t_command *cmd)
{
	char	**argv;

	if (!cmd || !cmd->arg_lst || !cmd->arg_lst->content)
		return ;
	expand_args(data, cmd);
	if (redirect_fd(data, cmd) == ERROR)
	{
		ft_printf_fd(2, "single builtin no redirect\n");
		return ;
	}
	argv = get_cmd_args_arr(cmd);
	if (!argv)
		return ;
	if (ft_strcmp(cmd->arg_lst->content, "exit") == 0)
		data->exit_code = ft_exit(data, argv);
	else if (ft_strcmp(cmd->arg_lst->content, "pwd") == 0)
		data->exit_code = ft_pwd();
	else if (ft_strcmp(cmd->arg_lst->content, "cd") == 0)
		data->exit_code = ft_cd(data->env, argv);
	else if (ft_strcmp(cmd->arg_lst->content, "env") == 0)
		data->exit_code = ft_env(data->env);
	else if (ft_strcmp(cmd->arg_lst->content, "echo") == 0)
		data->exit_code = ft_echo(argv);
	else if (ft_strcmp(cmd->arg_lst->content, "export") == 0)
		data->exit_code = ft_export(data->env, argv);
	else if (ft_strcmp(cmd->arg_lst->content, "unset") == 0)
		data->exit_code = ft_unset(data->env, argv);
	else
		return (ft_free_tab(argv));
	
	return (ft_free_tab(argv));
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
	current = *waitlist;
	i = 0;
	if (!current->next && is_builtin(current->content))
	{
		exec_single_builtin(data, current->content);
		clear_waitlist(waitlist);
		return ;
	}
	init_exec(data, &exec, child_count);
	while (current)
	{
		cmd = current->content;
		expand_args(data, cmd);
		// if (!current->next && is_builtin(cmd))
		// {
		// 	if (redirect_fd(data, cmd) == ERROR)
		// 		{
		// 			ft_printf_fd(2, "single builtin no redirect\n");
		// 		return ;
		// 		}
		// 	exec_builtin(data, cmd);
		// 	// ft_printf_fd(2, "single builtin fd\n", );
		// 	// restore_fd(data);
		// 	return ;
		// }
		data->status = exec_cmd(data, cmd, &exec, !(current->next));
		exec.child_pids[i++] = exec.pid;
		current = current->next;
	}
	data->exit_code = wait_child(exec.child_pids, child_count);
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

