/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:06:14 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/20 20:28:16 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_heredoc(int fd, char *eof)
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
		buff = replace_key(buff, )
		write(fd, buff, ft_strlen(buff));
		write(fd, "\n", 1);
		free(buff);
	}
	free(buff);
}

static int	get_heredoc(char *eof)
{
	int	fd;

	if (!eof)
		return (0);
	unlink(".minishell.tmp");
	fd = open(".minishell.tmp", O_CREAT | O_RDWR, 0644);
	if (!fd)
		return (0);
	read_heredoc(fd, eof);
	close(fd);
	return (1);
}

int	parse_heredoc(t_redirection **redir_root)
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
			if (!get_heredoc(head->filename))
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
