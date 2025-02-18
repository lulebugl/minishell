/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:06:14 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/18 16:09:36 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool read_heredoc(int fd, char *eof)
{
	char	*buff;

	while (true)
	{
		buff = NULL;
		buff = readline("> ");
		
	}
}

char	*get_heredoc(t_redirection *redirections)
{
	
}
