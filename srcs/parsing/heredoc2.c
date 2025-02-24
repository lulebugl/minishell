/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:06:14 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/20 20:30:59 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_sigint_handler(int sig)
{
	pid_t	pid;
	int		status;

	g_sig = sig;
	pid = waitpid(-1, &status, 0);
	if (WTERMSIG(status) == SIGINT || (pid > 0 && (WIFSIGNALED(status)
				&& WTERMSIG(status) == SIGINT)))
		write(2, "\n", 1);
	else
	{
		// write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		// print_details();
		// rl_redisplay();
		exit(130);
	}
	g_sig = sig;
}

static void	init_heredoc_signals(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_flags = SA_RESTART;
	sigemptyset(&act.sa_mask);
	act.sa_handler = &heredoc_sigint_handler;
	sigaction(SIGINT, &act, NULL);
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

static void	read_heredoc(int fd, char *eof)
{
	char	*buff;
	int		i;
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		i = 0;
		while (true)
		{
			init_heredoc_signals();
			buff = readline("> ");
			reset_sigquit();
			i++;
			if (!buff)
			{
				ft_printf_fd(2,
								"minishell: warning: here-document at line %d \
delimited by end-of-file (wanted '%s')\n",
								i,
								eof);
				exit(0);
			}
			if (ft_strcmp(buff, eof) == 0)
			{
				free(buff);
				exit(0);
			}
			write(fd, buff, ft_strlen(buff));
			write(fd, "\n", 1);
			free(buff);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) || WEXITSTATUS(status) == 130)
			g_sig = SIGINT;
	}
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

