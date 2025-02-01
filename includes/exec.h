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

#include "minishell.h"

// Execution context to track state
typedef struct s_exec_context
{
	int stdin_backup;  // For restoring stdin
	int stdout_backup; // For restoring stdout
	int pipe_read;     // Read end of current pipe
	int pipe_write;    // Write end of current pipe
	// int     exit_status;   // Last command's exit status
	// t_env   *env;          // Environment variables
}	t_exec_context;

int	exec(t_data *data);