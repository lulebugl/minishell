/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:09:25 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/28 19:09:26 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"

static int	count_args_until_operator(t_token *start)
{
	t_token	*curr;
	int		count;

	count = 0;
	curr = start;
	while (curr && curr->type == TOKEN_WORD)
	{
		count++;
		curr = curr->next;
	}
	return (count);
}

static char	**create_args_array(t_token *start, int arg_count)
{
	char	**args;
	int		i;
	t_token	*curr;

	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	curr = start;
	i = 0;
	while (i < arg_count)
	{
		args[i] = ft_strdup(curr->content);
		if (!args[i])
		{
			while (--i >= 0)
				free(args[i]);
			free(args);
			return (NULL);
		}
		curr = curr->next;
		i++;
	}
	args[arg_count] = NULL;
	return (args);
}

static t_redirection	*create_redirection(t_token *token)
{
	t_redirection	*redir;

	if (!token->next || token->next->type != TOKEN_WORD)
		return (NULL);
	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	if (token->type == TOKEN_IN)
		redir->type = TOKEN_IN;
	else if (token->type == TOKEN_OUT)
		redir->type = TOKEN_OUT;
	else if (token->type == TOKEN_APPEND)
		redir->type = TOKEN_APPEND;
	else
		redir->type = TOKEN_HEREDOC;
	redir->filename = ft_strdup(token->next->content);
	if (!redir->filename)
	{
		free(redir);
		return (NULL);
	}
	// redir->fd = -1;
	return (redir);
}

static int	add_redirections(t_command *cmd, t_token *start)
{
	t_token			*curr;
	t_redirection	*redir;

	curr = start;
	while (curr && curr->type == TOKEN_WORD)
		curr = curr->next;
	while (curr && (curr->type == TOKEN_IN || curr->type == TOKEN_OUT
			|| curr->type == TOKEN_APPEND || curr->type == TOKEN_HEREDOC))
	{
		redir = create_redirection(curr);
		if (!redir)
			return (0);
		ast_add_redirection(cmd, redir);
		curr = curr->next->next;
	}
	return (1);
}

t_ast_node *create_command(t_token *token)
{
    t_ast_node  *node;
    int         arg_count;
    char        **args;

    //printf("\n=== Starting create_command ===\n");
    if (!token)
        return (NULL);
    //printf("Token type: %d, content: '%s'\n", token->type, token->content);
    if (token->type != TOKEN_WORD)
        return (NULL);

    arg_count = count_args_until_operator(token);
    //printf("Found %d arguments\n", arg_count);
    if (arg_count == 0)
        return (NULL);
    args = create_args_array(token, arg_count);
    if (!args)
        return (NULL);

    node = ast_create_command(args, arg_count);
    if (!node)
    {
        //printf("Error: Failed to create AST node\n");
        return ( ft_free_tab(args), NULL);
    }

    // if (!add_redirections(node->cmd, token))
    // {
    //     printf("Error: Failed to add redirections\n");
    //     // free_ast(node);
    //     return (NULL);
    // }

    return (node);
}
