/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:07:07 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/20 16:40:05 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expander(t_data *data, t_command *cmd)
{
	if (!data || !cmd || !cmd->arg_lst)
		return (1);
	if (expand_tilde(data, cmd->arg_lst) != SUCCESS)
		return (1);
	if (expand_keys(data, cmd->arg_lst) != SUCCESS)
		return (1);
	if (split_expanded_arguments(data, cmd) != SUCCESS)
		return (1);
	if (expand_wildcards(cmd) != SUCCESS)
		return (1);
	if (remove_quotes(data, cmd->arg_lst) != SUCCESS)
		return (1);
	// debug_expander(cmd);
	cmd->arg_count = ft_lstsize(cmd->arg_lst);
	return (SUCCESS);
}
