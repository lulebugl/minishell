/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:50:09 by maxweert          #+#    #+#             */
/*   Updated: 2024/09/15 20:58:27 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_remove_if(t_list **begin_list, void *data_ref,
		int (*cmp)(), void (*free_fct)(void *))
{
	t_list	*previous;
	t_list	*tmp;
	t_list	*head;

	previous = 0;
	head = *begin_list;
	while (head)
	{
		if ((*cmp)(head->content, data_ref) == 0)
		{
			tmp = head->next;
			(*free_fct)(head->content);
			free(head);
			head = tmp;
			if (previous)
				previous->next = head;
			else
				*begin_list = head;
		}
		else
		{
			previous = head;
			head = head->next;
		}
	}
}
