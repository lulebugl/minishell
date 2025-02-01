/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:59:53 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/31 19:59:54 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "minishell.h"

// Execution context to track state
typedef struct s_exec
{
	int stdin_backup;  // For restoring stdin
	int stdout_backup; // For restoring stdout
	int fd_in;
	int fd_out;
	pid_t *child_pids;
	int pipe_read;     // Read end of current pipe
	int pipe_write;    // Write end of current pipe
}	t_exec;

int	exec(t_data *data);
int	exec_debug(t_data *data);


#endif