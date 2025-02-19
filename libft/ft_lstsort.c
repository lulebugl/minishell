/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:50:55 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/19 12:55:00 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_swap_lst(t_list *lst1, t_list *lst2)
{
	t_list	*tmp;

	tmp = lst2->next;
	lst2->next = lst1;
	lst1->next = tmp;
	return (lst2);
}

void	ft_lstsort(t_list **begin_list, int (*cmp)())
{
	int		lst_size;
	int		i;
	int		j;
	t_list	**head;

	lst_size = ft_lstsize(*begin_list);
	i = 0;
	while (i < lst_size)
	{
		j = 0;
		head = begin_list;
		while (j < lst_size - 1 - i)
		{
			if ((*head) && (*head)->next && (*cmp)((*head)->content,
				(*head)->next->content) > 0)
				*head = ft_swap_lst((*head), (*head)->next);
			head = &(*head)->next;
			j++;
		}
		i++;
	}
}
