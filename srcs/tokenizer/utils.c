/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:01:18 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/18 17:01:20 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void clear_tokens(t_token **tokens)
{
	if (tokens && *tokens)
	{
		if ((*tokens)->next)
			clear_tokens(&(*tokens)->next);
		free((*tokens)->content);
		*tokens = NULL;
	}
}

t_token	*new_token(char *content, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(t_token));
	new->content = content;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	push_token(t_token **lst, t_token *node)
{
	t_token	*tmp;

	tmp = *lst;
	if (lst && !(*lst))
		*lst = node;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

void	msg_unexpected_token(char token)
{
	ft_printf_fd(STDERR_FILENO,
		"minishell: syntax error near unexpected token `%c'\n", token);
}

void	msg_custom_err(char *msg, char *details)
{
	ft_printf_fd(STDERR_FILENO, "minishell: ");
	if (details)
		ft_printf_fd(STDERR_FILENO, details);
	if (msg)
		ft_printf_fd(STDERR_FILENO, msg);
}
