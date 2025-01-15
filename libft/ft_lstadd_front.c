/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:55:17 by llebugle          #+#    #+#             */
/*   Updated: 2024/10/25 14:15:03 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *node)
{
	t_list	*tmp;

	tmp = *lst;
	*lst = node;
	node->next = tmp;
}

// int main(int ac, char **av)
// {
// 	t_list *begin;

// 	begin = ft_lstnew((int*)9);
// 	begin->next = ft_lstnew((int*)3); 
// 	begin->next->next = ft_lstnew((int*)5);
// 	ft_lstadd_front(&begin, ft_lstnew((int*)1));
// 	while (begin)
// 	{
// 		printf("%d,", (int)begin->content);
// 		begin = begin->next;
// 	}
// 	return (0);
// }