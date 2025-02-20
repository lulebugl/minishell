/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:17:54 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/20 19:54:29 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_cmd_args_arr(t_command *cmd)
{
	char	**arr;
	t_list	*head;
	int		i;

	arr = malloc(sizeof(char *) * (cmd->arg_count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	head = cmd->arg_lst;
	while (head && i < cmd->arg_count)
	{
		arr[i] = ft_strdup(head->content);
		if (!arr[i])
		{
			i--;
			while (i > 0)
				free(arr[i--]);
			free(arr);
			return (NULL);
		}
		i++;
		head = head->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->arg_lst)
		ft_lstclear(&(cmd->arg_lst), &free);
	if (cmd->redirections)
		free_redirections(cmd->redirections);
	free(cmd);
}

int	token_is_part_of_command(t_token_type token_type)
{
	if (token_type == TOKEN_WORD)
		return (1);
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

static int	set_command(t_token **token, t_command *cmd)
{
	t_token_type	type;

	if ((*token)->type == TOKEN_WORD)
	{
		if (ft_strchr((*token)->content, '*'))
		{
			if (ft_strchr((*token)->content, '/'))
				return (printf("minishell: wildcard in another \
					directory not implemented.\n"), 0);
		}
		ft_lstadd_back(&(cmd->arg_lst),
			ft_lstnew(ft_strdup((*token)->content)));
	}
	else
	{
		type = (*token)->type;
		*token = (*token)->next;
		if (ft_strchr((*token)->content, '*'))
			return (printf("minishell: wildcard in \
				redirection not implemented.\n"), 0);
		add_redirection(&(cmd->redirections),
			new_redirection(type, (*token)->content));
	}
	*token = (*token)->next;
	return (1);
}

t_command	*get_command(t_token **token)
{
	t_command		*cmd;

	if (!token || !*token)
		return (NULL);
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	ft_bzero(cmd, sizeof(t_command));
	while (*token && token_is_part_of_command((*token)->type))
		if (!set_command(token, cmd))
			return (free_command(cmd), NULL);
	cmd->arg_count = ft_lstsize(cmd->arg_lst);
	cmd->redir_count = count_redirections(cmd->redirections);
	if (!parse_heredoc(&(cmd->redirections)))
		return (NULL);
	return (cmd);
}
