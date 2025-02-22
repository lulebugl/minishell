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

static void heredoc_sigint_handler(int sig)
{
    (void)sig;
    write(2, "\n", 1);
    exit(130);  // Exit heredoc with special status
}

static void init_heredoc_signals(void)
{
    struct sigaction act;
    
    ft_bzero(&act, sizeof(act));
    act.sa_flags = SA_RESTART;
    sigemptyset(&act.sa_mask);
    
    // Set SIGINT handler
    act.sa_handler = &heredoc_sigint_handler;
    sigaction(SIGINT, &act, NULL);
    
    // Ignore SIGQUIT
    act.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &act, NULL);
}

static void read_heredoc(int fd, char *eof)
{
    char *buff;
    int i;
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        // Child process
        init_heredoc_signals();
        
        i = 0;
        while (true)
        {
            buff = readline("> ");
            i++;
            if (!buff)
            {
                ft_printf_fd(2, "minishell: warning: here-document at line %d \
delimited by end-of-file (wanted '%s')\n", i, eof);
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
        // Parent process
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
