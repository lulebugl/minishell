/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:41:55 by maxweert          #+#    #+#             */
/*   Updated: 2025/01/30 23:44:39 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"

static int	count_args(t_token *start)
{
	int	count;

	count = 0;
	while (start && start->type == TOKEN_WORD)
	{
		count++;
		start = start->next;
	}
	return (count);
}

static char	**get_args(t_token **start, int arg_count)
{
	char	**args;
	int		i;

	i = 0;
	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	ft_bzero(args, (sizeof(char *) * (arg_count + 1)));
	i = 0;
	while ((*start) && i < arg_count)
	{
		args[i] = ft_strdup((*start)->content);
		if (!args[i])
		{
			free_str_arr(args);
			return (NULL);
		}
		*start = (*start)->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

void	free_command(t_command *cmd)
{
	free_str_arr(cmd->args);
	free_redirections(cmd->redirections);
	free(cmd);
}

t_command	*get_command(t_token **token)
{
	t_token		*head;
	t_command	*cmd;

	if (!token || !*token)
		return (NULL);
	head = *token;
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	ft_bzero(cmd, sizeof(t_command));
	cmd->arg_count = count_args(*token);
	cmd->args = get_args(token, cmd->arg_count);
	if (!cmd->args)
		return (free_command(cmd), NULL);
	cmd->redirections = get_redirections(&(*token));
	cmd->redir_count = count_redirections(cmd->redirections);
	return (cmd);
}
