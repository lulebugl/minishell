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

int split_words(t_data *data, t_command *cmd);

bool	skip_quoted(char *str, int *i)
{
	if (!str || (str[*i] != SINGLE_QUOTE && str[*i] != DOUBLE_QUOTE))
		return (false);
	if (str[*i] == SINGLE_QUOTE)
	{
		(*i)++;
		while (str[*i] && str[*i] != SINGLE_QUOTE)
			(*i)++;
		if (str[*i] == SINGLE_QUOTE)
			(*i)++;
		return (true);
	}
	else if (str[*i] == DOUBLE_QUOTE)
	{
		(*i)++;
		while (str[*i] && str[*i] != DOUBLE_QUOTE)
			(*i)++;
		if (str[*i] == DOUBLE_QUOTE)
			(*i)++;
		return (true);
	}
	return (true);
}

// static char	*expand_str_wildcards(t_data *data, char *arg)
// {
// 	int	i;

// 	i = 0;
// 	if (!arg)
// 		return (NULL);
// 	while (arg[i])
// 	{
// 		if (skip_quoted(arg, &i) == true)
// 			continue ;
// 		if (arg[i] && arg[i] == '*')
// 		{
// 			arg = expand_var(data, arg, &i);
// 			if (!arg)
// 				err_and_exit(data);
// 			continue ;
// 		}
// 		i++;
// 	}
// 	return (arg);
// }

static int	handle_wildcards(t_list **args, t_list **prev,
		t_command *cmd)
{
	if (!*prev)
	{
		if (expand_wildcard(args))
			return (1);
		cmd->arg_lst = *args;
	}
	else
	{
		if (expand_wildcard(args))
			return (1);
		(*prev)->next = *args;
	}
	return (0);
}

int	expand_wildcards(t_data *data, t_command *cmd)
{
	t_list	*curr;
	t_list	*prev;
	char	*arg;

	if (!cmd || !cmd->arg_lst)
		return (ERROR);
	curr = cmd->arg_lst;
	prev = NULL;
	while (curr)
	{
		if (!curr->content)
		{
			curr = curr->next;
			continue ;
		}
		handle_wildcards(&curr, &prev, cmd);
		prev = curr;
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
    if (expand_wildcards(data, cmd) != SUCCESS)
        return (1);
    if (remove_quotes(data, cmd->arg_lst) != SUCCESS)
        return (1);
    //debug_expander(cmd);
    cmd->arg_count = ft_lstsize(cmd->arg_lst);
    return (SUCCESS);
}


