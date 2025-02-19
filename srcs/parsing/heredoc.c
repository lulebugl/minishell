/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:06:14 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/18 17:59:58 by maxweert         ###   ########.fr       */
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
		write(fd, buff, ft_strlen(buff));
		write(fd, "\n", 1);
		free(buff);
	}
	free(buff);
}

int	get_heredoc(char *eof)
{
	int	fd;

	unlink(".minishell.tmp");
	fd = open(".minishell.tmp", O_CREAT | O_RDWR, 0644);
	if (!fd)
		return (0);
	read_heredoc(fd, eof);
	close(fd);
	return (1);
}
