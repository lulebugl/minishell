/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:19:43 by llebugle          #+#    #+#             */
/*   Updated: 2024/10/25 14:28:13 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	last = lst;
	while (last && last->next)
		last = last->next;
	return (last);
}

// int main(int ac, char **av)
// {
// 	t_list *begin;
// 	t_list *last;

// 	begin = ft_lstnew((int*)9);
// 	begin->next = ft_lstnew((int*)3);
// 	begin->next->next = ft_lstnew((int*)5);
// 	begin->next->next->next = ft_lstnew((int*)6);
// 	last = ft_lstlast(begin);
// 	printf("%d,", (int)last->content);
// 	return (0);
// }
