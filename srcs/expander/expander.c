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

static bool	has_unquoted_space(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == SINGLE_QUOTE)
		{
			i++;
			while (str[i] && str[i] != SINGLE_QUOTE)
				i++;
			if (str[i])
				i++;
		}
		else if (str[i] == DOUBLE_QUOTE)
		{
			i++;
			while (str[i] && str[i] != DOUBLE_QUOTE)
				i++;
			if (str[i])
				i++;
		}
		else if (str[i] == ' ')
			return (true);
		else
			i++;
	}
	return (false);
}

/*
 * Function: split_expanded_arguments
 * ----------------------------
 * After parameter expansion, some arguments might contain spaces
 * from expanded environment variables. This function splits those.
 */
int	split_expanded_arguments(t_data *data, t_command *cmd)
{
	t_list	*curr;
	t_list	*next;
	t_list	*prev;

	if (!cmd || !cmd->arg_lst)
		return (SUCCESS);
	curr = cmd->arg_lst;
	prev = NULL;
	while (curr)
	{
		next = curr->next;
		if (curr->content && has_unquoted_space(curr->content))
		{
			if (separate_expanded(data, curr) != SUCCESS)
				return (ERROR);
			if (!prev)
				cmd->arg_lst = curr;
			else
				prev->next = curr;
			while (curr && curr->next)
			{
				prev = curr;
				curr = curr->next;
			}
			curr->next = next;
		}
		else
			prev = curr;
		curr = next;
	}
	return (SUCCESS);
}

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
