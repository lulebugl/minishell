/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:59:53 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/20 19:12:23 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "structures.h"

# define DOUBLE_QUOTE 34
# define SINGLE_QUOTE 39
# define APPEND 1
# define TRUNC 2

void	child_process(t_data *data, t_command *cmd, t_exec *exec, bool last);
int		exec(t_data *data);
int		exec_cmd(t_data *data, t_command *cmd, t_exec *exec, bool last);

/* utils */
void	init_exec(t_data *data, t_exec *exec, t_list **wailtist);
int		wait_child(pid_t *child_pids, int child_count);
char	**t_env_to_envp(t_env *env);

/* redirect */

int		redirect_fd(t_data *data, t_command *cmd);
void	restore_fd(t_data *data);

/* path */

char	*try_relative(t_data *data, char *str);
char	*get_path(t_data *data, char *str, t_env *env);

/* builtins */

int		exec_builtin(t_data *data, t_command *cmd);
bool	is_builtin(t_command *cmd);
void	exec_single_builtin(t_data *data, t_command *cmd);
int		exec_builtin(t_data *data, t_command *cmd);

#endif

