/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:59:53 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/04 21:26:03 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "structures.h"

void	child_process(t_data *data, t_command *cmd, t_exec *exec, bool last);
char	**t_env_to_envp(t_env *env);

int		exec(t_data *data);
int		exec_debug(t_data *data);
int		is_builtin(t_data *data, t_command *cmd, t_exec *exec);

int		expander_new(t_data *data, char **argv, int ac);
void	wait_child(t_data *data, pid_t *child_pids, int child_count);
void	init_exec(t_data *data, t_exec *exec, int child_count);
int		exec_cmd(t_data *data, t_command *cmd, t_exec *exec, bool last);

char	*get_path(char *str, t_env *env);

#endif

