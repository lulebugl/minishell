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

# include "structures.h"

void child_process(t_data *data, t_command *cmd, t_exec *exec);
void parent_process(t_exec *exec);
char	**t_env_to_envp(t_env *env);


int			exec(t_data *data);
int			exec_debug(t_data *data);

#endif

