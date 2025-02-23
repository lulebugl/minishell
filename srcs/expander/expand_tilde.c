/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:15:32 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/23 16:15:33 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_home(t_data *data, char *arg, t_list *curr)
{
	char	*home;

	home = env_get_value(data->env, "HOME");
	if (!home)
		return (1);
	if (arg[1] == '\0')
		curr->content = ft_strdup(home);
	else
		curr->content = ft_strjoin(home, arg + 1);
	if (!curr->content)
		err_and_exit(data);
	free(arg);
	return (0);
}

int	expand_tilde2(t_data *data, t_list *args)
{
	t_list	*curr;
	char	*arg;

	if (!args)
		return (0);
	curr = args;
	while (curr)
	{
		arg = curr->content;
		if (!arg || !arg[0] || arg[0] != '~')
		{
			curr = curr->next;
			continue ;
		}
		if (arg[1] == '\0' || arg[1] == '/')
		{
			if (replace_home(data, arg, curr))
			{
				curr = curr->next;
				continue ;
			}
		}
		curr = curr->next;
	}
	return (0);
}

