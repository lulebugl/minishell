/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 21:08:00 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/24 21:08:01 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_wildcard(t_list **current)
{
	t_list	*tmp;
	t_list	*matches;

	if (!current || !*current || is_quote(((char *)(*current)->content)[0]))
		return ;
	if (!ft_strchr((*current)->content, '*'))
		;
	tmp = *current;
	matches = find_matchs((*current)->content);
	*current = matches;
	ft_lstlast(matches)->next = tmp->next;
	free(tmp->content);
	free(tmp);
}

int	expand_wildcards(t_command *cmd)
{
	t_list	*curr;
	t_list	*prev;

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
		expand_wildcard(&curr);
		if (!prev)
			cmd->arg_lst = curr;
		else
			prev->next = curr;
		prev = curr;
		curr = curr->next;
	}
	return (0);
}
