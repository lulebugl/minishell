/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:49:25 by maxweert          #+#    #+#             */
/*   Updated: 2025/01/30 23:29:25 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"

void	free_redirections(t_redirection *root)
{
	t_redirection	*tmp;

	if (!root)
		return ;
	while (root)
	{
		tmp = root->next;
		if (root->filename)
			free(root->filename);
		free(root);
		root = tmp;
	}
}

int	count_redirections(t_redirection *root)
{
	int	i;

	i = 0;
	while (root)
	{
		i++;
		root = root->next;
	}
	return (i);
}

static t_redirection	*new_redirection(t_token_type type, char *filename)
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

static void	add_redirection(t_redirection **root, t_redirection *new)
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

t_redirection	*get_redirections(t_token **token)
{
	t_token_type	type;
	t_redirection	*root_redir;
	t_redirection	*elem_redir;

	root_redir = NULL;
	if (!*token || !token_is_redir(*token))
		return (NULL);
	while (*token && token_is_redir(*token))
	{
		type = (*token)->type;
		*token = (*token)->next;
		if (!*token)
			return (NULL);
		elem_redir = new_redirection(type, (*token)->content);
		if (!elem_redir)
		{
			free_redirections(root_redir);
			return (NULL);
		}
		add_redirection(&root_redir, elem_redir);
		*token = (*token)->next;
	}
	return (root_redir);
}
