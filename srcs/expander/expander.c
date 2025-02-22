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

static int	handle_empty_quotes(t_data *data, t_list *args)
{
	char	*arg;

	arg = args->content;
	if (ft_strcmp(arg, "\"\"") == 0 || ft_strcmp(arg, "\'\'") == 0)
	{
		free(args->content);
		args->content = ft_strdup("");
		if (!args->content)
			err_and_exit(data);
		return (1);
	}
	return (0);
}

char	*remove_quotes2(t_data *data, char *str, bool *expand, int *quoted);

static int	process_argument(t_data *data, t_list *args, bool *expand,
		int *quoted)
{
	char	*arg;

	arg = args->content;
	args->content = remove_quotes(data, arg, expand, quoted);
	if (!arg)
		return (1);
	if (expand_tilde(data, args, *expand))
		return (1);
	if (expand_arg_recursive(data, args, *expand))
		return (1);
	return (0);
}

static int	handle_wildcards(t_list **args, t_list **prev,
		t_command *cmd)
{
	if (!*prev)
	{
		if (expand_wildcards(args))
			return (1);
		cmd->arg_lst = *args;
	}
	else
	{
		if (expand_wildcards(args))
			return (1);
		(*prev)->next = *args;
	}
	return (0);
}

static int expand_args(t_data *data, t_command *cmd, t_list **args, t_list **prev)
{
    t_list *next;
    bool expand;
    int quoted;

    next = (*args)->next;
    if (!(*args)->content)
        return (*args = next, 0);
    if (handle_empty_quotes(data, *args))
    {
        *args = next;
        return (0);
    }
    expand = true;
    if (process_argument(data, *args, &expand, &quoted))
        return (1);
    //del_empty_args(&cmd->arg_lst, *args);
    if (!quoted && *args)
        separate_expanded(data, *args);
    if (!quoted && (*args)->content && ft_strchr((*args)->content, '*'))
        if (handle_wildcards(args, prev, cmd))
            return (1);
    return (*prev = *args, *args = next, 0);
}

int	expander(t_data *data, t_command *cmd)
{
	t_list	*args;
	t_list	*prev;

	prev = NULL;
	if (!data || !cmd || !cmd->arg_lst)
		return (1);
	args = cmd->arg_lst;
	while (args)
		if (expand_args(data, cmd, &args, &prev))
			return (1);
	debug_expander(cmd);
	cmd->arg_count = ft_lstsize(cmd->arg_lst);
	return (0);
}

