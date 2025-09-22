/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:31:41 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/18 19:06:36 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	debug_expander(t_command *cmd)
{
	t_list	*arg;

	arg = cmd->arg_lst;
	printf("-- After expander --\n");
	while (arg)
	{
		printf(" [%s] ", (char *)arg->content);
		arg = arg->next;
	}
	printf("\n---------------\n");
	return (0);
}

void	debug_cmd(t_data *data, t_command *cmd)
{
	t_list	*tmp;

	if (!cmd || !cmd->arg_lst || !cmd->arg_lst->content || cmd->arg_count == 0)
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
			tmp = cmd->arg_lst;
			while (tmp)
			{
				printf("%s ", (char *)tmp->content);
				tmp = tmp->next;
			}
		}
		printf("\n");
		debug_expander(cmd);
	}
}
