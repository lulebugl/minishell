/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:03:30 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/20 19:15:08 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	padding(char ch, int n)
{
	int	i;

	for (i = 0; i < n; i++)
		putchar(ch);
}

void	print_command(t_command *cmd)
{
	t_redirection	*head_redir;
	t_list			*head_args;

	printf(COLOR_WORD);
	head_redir = cmd->redirections;
	head_args = cmd->arg_lst;
	while (head_args)
	{
		printf("%s ", (char *)head_args->content);
		head_args = head_args->next;
	}
	printf(COLOR_REDIR);
	while (head_redir)
	{
		printf("%s ", head_redir->filename);
		head_redir = head_redir->next;
	}
	printf(COLOR_RESET);
}

void	print_ast(t_tree_node *root, int level)
{
	if (root == NULL)
	{
		padding('\t', level);
		puts("~");
	}
	else
	{
		print_ast(root->right, level + 1);
		padding('\t', level);
		switch (root->type)
		{
		case NODE_AND:
			printf("AND");
			break ;
		case NODE_OR:
			printf("OR");
			break ;
		case NODE_PIPE:
			printf("PIPE");
			break ;
		case NODE_COMMAND:
			print_command(root->cmd);
			break ;
		default:
			break ;
		}
		printf("\n");
		print_ast(root->left, level + 1);
	}
}