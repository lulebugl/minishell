/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:06:14 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/20 22:23:40 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_heredoc(t_data *data, int fd, char *buff)
{
	int		i;
	int		start;
	char	*var;
	char	*value;

	i = 0;
	start = 0;
	while (buff[i])
	{
		if (buff[i] == '$')
		{
			write(fd, &buff[start], i - start);
			i++;
			if (buff[i] == '?')
			{
				var = ft_itoa(data->exit_code);
				write(fd, var, ft_strlen(var));
				free(var);
				i++;
			}
			else
			{
				start = i;
				while (buff[i] && (ft_isalnum(buff[i]) || buff[i] == '_'))
					i++;
				var = ft_strndup(&buff[start], i - start);
				if (env_key_exists(data->env, var))
					value = env_get_value(data->env, var);
				else
					value = "";
				write(fd, value, ft_strlen(value));
				free(var);
			}
			start = i;
		}
		else
			i++;
	}
	write(fd, &buff[start], i - start);
}

static void	read_heredoc(t_data *data, int fd, char *eof)
{
	char	*buff;
	int		i;

	i = 0;
	while (true)
	{
		buff = NULL;
		buff = readline("> ");
		i++;
		if (!buff)
		{
			ft_printf_fd(2, "minishell: warning: here-document at line %d \
delimited by end-of-file (wanted '%s')\n", i, eof);
			break ;
		}
		if (ft_strcmp(buff, eof) == 0)
			break ;
		write_heredoc(data, fd, buff);
		write(fd, "\n", 1);
		free(buff);
	}
	free(buff);
}

static int	get_heredoc(t_data *data, char *eof)
{
	int	fd;

	if (!eof)
		return (0);
	unlink(".minishell.tmp");
	fd = open(".minishell.tmp", O_CREAT | O_RDWR, 0644);
	if (!fd)
		return (0);
	read_heredoc(data, fd, eof);
	close(fd);
	return (1);
}

int	parse_heredoc(t_data *data, t_redirection **redir_root)
{
	t_redirection	*head;
	t_redirection	*last_hdoc;

	head = *redir_root;
	last_hdoc = NULL;
	while (head)
	{
		if (head->type == TOKEN_HEREDOC)
		{
			init_signals();
			if (!get_heredoc(data, head->filename))
				return (0);
			reset_sigquit();
			free(head->filename);
			head->filename = NULL;
			last_hdoc = head;
		}
		head = head->next;
	}
	if (last_hdoc)
		last_hdoc->filename = ft_strdup(".minishell.tmp");
	if (last_hdoc && !last_hdoc->filename)
		return (0);
	return (1);
}
