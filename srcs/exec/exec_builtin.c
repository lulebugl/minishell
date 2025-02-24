/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:30:24 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/20 21:30:27 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_command *cmd)
{
	if (!cmd || !cmd->arg_lst || !cmd->arg_lst->content)
		return (0);
	if (ft_strcmp(cmd->arg_lst->content, "exit") == 0)
		return (true);
	else if (ft_strcmp(cmd->arg_lst->content, "pwd") == 0)
		return (true);
	else if (ft_strcmp(cmd->arg_lst->content, "cd") == 0)
		return (true);
	else if (ft_strcmp(cmd->arg_lst->content, "env") == 0)
		return (true);
	else if (ft_strcmp(cmd->arg_lst->content, "echo") == 0)
		return (true);
	else if (ft_strcmp(cmd->arg_lst->content, "export") == 0)
		return (true);
	else if (ft_strcmp(cmd->arg_lst->content, "unset") == 0)
		return (true);
	else
		return (false);
}

void	pre_exit(t_data *data, char **argv, t_exec *exec)
{
	cleanup_exec(exec);
	restore_fd(data);
	data->exit_code = ft_exit(data, argv);
}

int	exec_builtin(t_data *data, t_command *cmd, t_exec *exec)
{
	char	**argv;

	if (!cmd || !cmd->arg_lst || !cmd->arg_lst->content)
		return (0);
	argv = get_cmd_args_arr(cmd);
	if (!argv)
		return (0);
	if (ft_strcmp(cmd->arg_lst->content, "exit") == 0)
		pre_exit(data, argv, exec);
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
		return (ft_free_tab(argv), 0);
	return (ft_free_tab(argv), 1);
}

void	exec_single_builtin(t_data *data, t_command *cmd, t_exec *exec)
{
	char	**argv;

	if (!cmd || !cmd->arg_lst || !cmd->arg_lst->content || expander(data,
			cmd) == ERROR || redirect_fd(data, cmd) == ERROR)
		return (cleanup_exec(exec));
	argv = get_cmd_args_arr(cmd);
	if (!argv)
		return ;
	if (ft_strcmp(cmd->arg_lst->content, "exit") == 0)
		pre_exit(data, argv, exec);
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
	return (cleanup_exec(exec), restore_fd(data), ft_free_tab(argv));
}

