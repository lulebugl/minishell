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

static int	expand_heredoc(t_data *data, char **buff)
{
	int		i;
	int		j;
	char	*var;
	char	*start;
	char	*end;
	char	*str;

	i = 0;
	j = 0;
	str = *buff;
	while (str[i] && str[i] != '$')
		i++;
	if (!str[i])
		return (1);
	i++;
	while (str[i + j] && (ft_isalnum(str[i + j]) || str[i + j] == '_'))
		j++;
	var = ft_strndup(&(str[i]), j);
	start = ft_strndup(str, i - 1);
	end = ft_strdup(&(str[i + j]));
	if (!var || !start || !end)
		return (free(var), free(start), free(end), 0);
	if (!env_key_exists(data->env, var))
		str = ft_strjoin(start, end);
	else
	{
		str = ft_strjoin(start, env_get_value(data->env, var));
		str = ft_strjoin_n_free(str, end);
	}
	free(*buff);
	*buff = str;
	return (free(var), free(start), free(end), 1);
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
		while (ft_strchr(buff, '$'))
			expand_heredoc(data, &buff);
		write(fd, buff, ft_strlen(buff));
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
	{
		last_hdoc->filename = ft_strdup(".minishell.tmp");
		if (!last_hdoc->filename)
			return (0);
	}
	return (1);
}
