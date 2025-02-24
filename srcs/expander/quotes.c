/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:32:39 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/24 17:32:41 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *unquote_arg(char *arg)
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

int remove_quotes(t_data *data, t_list *args)
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
		curr->content = unquote_arg(arg);
		if (curr->content)
		{
			curr = curr->next;
			continue ;
		}
		curr = curr->next;
	}
	return (0);
}