/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:07:07 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/13 21:07:08 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_args(t_data *data, t_command *cmd)
{
	bool expand;
	int quoted;
	t_list *args;
	char *arg;
	t_list *next;
	t_list *prev;

	args = cmd->arg_lst;
	while (args)
	{
		next = args->next;
		arg = args->content;
		if (arg)
		{
			expand = true;
			if (ft_strcmp(arg, "\"\"") == 0 || ft_strcmp(arg, "\'\'") == 0)
			{
				free(args->content);
				args->content = ft_strdup("");
				if (!args->content)
					err_and_exit(data);
				args = next;
				continue ;
			}
			args->content = remove_quotes(arg, &expand, &quoted);
			if (!arg)
				return (1);
			if (expand_tilde(data, args, expand))
				return (1);
			if (expand_arg_recursive(data, args, expand))
				return (1);
			del_empty_args(&cmd->arg_lst, args);
			if (!quoted)
				separate_expanded(data, args);
			if (!quoted && ft_strchr(args->content, '*'))
			{
				if (expand_wildcards(&args))
					return (1);
				if (prev)
					prev->next = args;
				else
					cmd->arg_lst = args;
			}
			prev = args;
			args = next;
		}
		args = next;
	}
	debug_expander(cmd);
	cmd->arg_count = ft_lstsize(cmd->arg_lst);
	return (0);
}
