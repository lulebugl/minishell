/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:09:55 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/20 20:22:08 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_outfile(char *filename, int type)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (type == APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: %s\n", filename,
			strerror(errno));
		return (ERROR);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (ERROR);
	}
	return (SUCCESS);
}

int	process_infile(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: %s\n", filename,
			strerror(errno));
		return (ERROR);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (ERROR);
	}
	return (SUCCESS);
}

int	expand_redirection(t_data *data, char **str, t_token_type type)
{
	if (!*str)
		return (ERROR);
	if (type == TOKEN_HEREDOC)
		return (SUCCESS);
	*str = expand_str(data, *str);
	if (!*str)
		return (ERROR);
	*str = unquote_arg(*str);
	if (!*str)
		return (ERROR);
	return (SUCCESS);
}

int	process_redirections(t_data *data, t_command *cmd)
{
	t_redirection	*curr;

	if (!cmd)
		return (0);
	curr = cmd->redirections;
	while (curr)
	{
		if (!token_is_redir(curr->type))
			return (ERROR);
		expand_redirection(data, &curr->filename, curr->type);
		if (curr->type == TOKEN_IN)
			if (process_infile(curr->filename) == ERROR)
				return (data->exit_code = ERROR, ERROR);
		if (curr->type == TOKEN_OUT)
			if (process_outfile(curr->filename, TRUNC) == ERROR)
				return (data->exit_code = ERROR, ERROR);
		if (curr->type == TOKEN_APPEND)
			if (process_outfile(curr->filename, APPEND) == ERROR)
				return (data->exit_code = ERROR, ERROR);
		if (curr->type == TOKEN_HEREDOC && curr->filename)
			if (process_infile(curr->filename) == ERROR)
				return (data->exit_code = ERROR, ERROR);
		curr = curr->next;
	}
	return (unlink(".minishell.tmp"), 0);
}

int	redirect_fd(t_data *data, t_command *cmd)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
		return (ERROR);
	if (process_redirections(data, cmd) == ERROR)
	{
		if (saved_stdin != -1)
		{
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdin);
		}
		if (saved_stdout != -1)
		{
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdout);
		}
		return (ERROR);
	}
	data->saved_stdin = saved_stdin;
	data->saved_stdout = saved_stdout;
	return (SUCCESS);
}
