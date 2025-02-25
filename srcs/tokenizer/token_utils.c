/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:01:18 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/20 19:16:25 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	token_is_redir(t_token_type token_type)
{
	if (token_type == TOKEN_IN)
		return (1);
	if (token_type == TOKEN_OUT)
		return (1);
	if (token_type == TOKEN_APPEND)
		return (1);
	if (token_type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

int	add_token(t_token **tokens, const char *prompt, t_token_pos pos,
		t_token_type type)
{
	char	*token;

	token = ft_substr(prompt, pos.start, pos.len);
	if (!token)
		return (1);
	push_token(tokens, new_token(token, type));
	return (0);
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
