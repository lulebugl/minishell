/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:49:25 by maxweert          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/18 19:07:02 by maxweert         ###   ########.fr       */
=======
/*   Updated: 2025/02/05 17:41:21 by maxweert         ###   ########.fr       */
>>>>>>> 32c87f5 (modifs)
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_redirections(t_redirection *root)
{
	t_redirection	*head;
	int				ret;

	ret = 0;
	head = root;
	while (head)
	{
		ret++;
		head = head->next;
	}
	return (ret);
}

void	free_redirections(t_redirection *root)
{
	if (!root)
		return ;
	if (root->next)
		free_redirections(root->next);
	if (root->filename)
		free(root->filename);
	free(root);
}

t_redirection	*new_redirection(t_token_type type, char *filename)
{
	t_redirection	*elem;

	elem = malloc(sizeof(t_redirection));
	if (!elem)
		return (NULL);
	ft_bzero(elem, sizeof(t_redirection));
	elem->type = type;
	elem->filename = ft_strdup(filename);
	if (!elem->filename)
	{
		free(elem);
		return (NULL);
	}
	return (elem);
}

void	add_redirection(t_redirection **root, t_redirection *new)
{
	t_redirection	*head;

	if (root && !*root)
	{
		*root = new;
		return ;
	}
	head = *root;
	while (head->next)
		head = head->next;
	head->next = new;
}
