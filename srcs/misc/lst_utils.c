/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:50:32 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/23 20:50:34 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*del_node_and_join(t_list **head, t_list *node_to_delete)
{
	t_list	**curr;
	t_list	*tmp;

	if (!head || !*head)
		return (NULL);
	if (!node_to_delete)
		return (*head);
	curr = head;
	while (*curr && *curr != node_to_delete)
		curr = &(*curr)->next;
	if (*curr)
	{
		tmp = *curr;
		*curr = (*curr)->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
		return (*curr);
	}
	return (*head);
}
