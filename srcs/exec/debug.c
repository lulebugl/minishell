/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:31:41 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/04 21:56:26 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exec.h"
#include "minishell.h"

void	debug_cmd(t_data *data, t_command *cmd)
{
	int	i;

	i = -1;
	if (!cmd || !cmd->arg_lst || cmd->arg_count == 0)
		return ;
	if (ft_strcmp(cmd->arg_lst->content, "token") == 0)
		data->print_token ^= 1;
	if (ft_strcmp(cmd->arg_lst->content, "ast") == 0)
		data->print_ast ^= 1;
	if (ft_strcmp(cmd->arg_lst->content, "debug") == 0)
		data->exec_debug ^= 1;
	if (data->exec_debug)
	{
		for (int i = 0; i < cmd->arg_count; i++)
		{
			t_list *tmp;
			tmp = cmd->arg_lst;
			while (tmp)
			{
				printf("%s ", (char *)tmp->content);
				tmp = tmp->next;
			}
		}
		printf("\n");
	}
}
