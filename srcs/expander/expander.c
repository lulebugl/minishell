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

int expand_keys(t_data *data, t_list *args);
int split_words(t_data *data, t_command *cmd);

static char *unquote_arg(t_data *data, char *arg)
{
	int i;
	
	i = 0;
	while (arg[i])
	{
		if (arg[i] == SINGLE_QUOTE)
		{
			arg = str_del_char(arg, &arg[i]);
			if (!arg)
				return (NULL);
			while (arg[i] && arg[i] != SINGLE_QUOTE)
				i++;
			arg = str_del_char(arg, &arg[i]);
			if (!arg)
				return (NULL);
			if (!arg[i])
				return (arg);
		}
		else if (arg[i] == DOUBLE_QUOTE)
		{
			arg = str_del_char(arg, &arg[i]);
			if (!arg)
				return (NULL);
			while (arg[i] && arg[i] != DOUBLE_QUOTE)
				i++;
			arg = str_del_char(arg, &arg[i]);
			if (!arg)
				return (NULL);
			if (!arg[i])
				return (arg);
		}
		else
			i++;
	}
	return (arg);
}

int remove_quotes2(t_data *data, t_list *args)
{
	t_list	*curr;
	char	*arg;

	if (!args)
		return (0);
	curr = args;
	while (curr)
	{
		arg = curr->content;
		if (!arg)
		{
			curr = curr->next;
			continue ;
		}
		curr->content = unquote_arg(data, arg);
		if (curr->content)
		{
			curr = curr->next;
			continue ;
		}
		curr = curr->next;
	}
	return (0);
}

int expander(t_data *data, t_command *cmd)
{
    if (!data || !cmd || !cmd->arg_lst)
        return (1);
    if (expand_tilde(data, cmd->arg_lst) != SUCCESS)
        return (1);
    if (expand_keys(data, cmd->arg_lst) != SUCCESS)
        return (1);
    // if (split_words(data, cmd) != SUCCESS)
    //     return (1);
    // // 4. Handle pathname/wildcards expansion (only if unquoted)
    // if (expand_wildcards(data, cmd) != SUCCESS)
    //     return (1);

    // // 5. Finally remove quotes from all arguments
    if (remove_quotes2(data, cmd->arg_lst) != SUCCESS)
        return (1);
    debug_expander(cmd);
    cmd->arg_count = ft_lstsize(cmd->arg_lst);
    return (SUCCESS);
}

// int	expander(t_data *data, t_command *cmd)
// {
// 	t_list	*args;
// 	t_list	*prev;

// 	prev = NULL;
// 	if (!data || !cmd || !cmd->arg_lst)
// 		return (1);
// 	args = cmd->arg_lst;
// 	while (args)
// 		if (expand_args(data, cmd, &args, &prev))
// 			return (1);
// 	debug_expander(cmd);
// 	cmd->arg_count = ft_lstsize(cmd->arg_lst);
// 	return (0);
// }

