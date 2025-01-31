/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:03:30 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/30 23:45:50 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"

void padding ( char ch, int n )
{
  int i;

  for ( i = 0; i < n; i++ )
    putchar ( ch );
}

void  print_command(t_command *cmd)
{
      t_redirection *head;
      printf(COLOR_WORD);
      for (int i = 0; cmd->args[i]; i++)
        printf("%s ", cmd->args[i]);
      printf(COLOR_REDIR);
      head = cmd->redirections;
      for (int i = 0; i < cmd->redir_count; i++)
      {
        printf("%s ", head->filename);
        head = head->next;
      }
      printf(COLOR_RESET);
}

static void print_command_lucas(t_command *cmd, int level)
{
    for (int i = 0; i < level; i++)
        printf("  ");
    printf("CMD: ");
    for (int i = 0; i < cmd->arg_count; i++)
    {
        printf("%s", cmd->args[i]);
        if (i < cmd->arg_count - 1)
            printf(" ");
    }
    printf("\n");
}

void print_ast_lucas(t_tree_node *node, int level)
{
    if (!node)
        return;

    for (int i = 0; i < level; i++)
        printf("  ");

    switch (node->type)
    {
        case NODE_COMMAND:
            print_command_lucas(node->cmd, 0);
            break;
        case NODE_PIPE:
            printf("PIPE:\n");
            break;
        case NODE_AND:
            printf("AND\n");
            print_ast_lucas(node->left, level + 1);
            print_ast_lucas(node->right, level + 1);
            break;
        case NODE_OR:
            printf("OR\n");
            print_ast_lucas(node->left, level + 1);
            print_ast_lucas(node->right, level + 1);
            break;
    }
}

void print_ast (t_tree_node *root, int level)
{
  int i;

  if ( root == NULL ) {
    padding ( '\t', level );
    puts ( "~" );
  }
  else {
    print_ast ( root->right, level + 1 );
    padding ( '\t', level );
	switch (root->type)
	{
    case NODE_AND:
      printf("AND");
      break;
    case NODE_OR:
      printf("OR");
      break;
    case NODE_PIPE:
      printf("PIPE");
      break;
    case NODE_COMMAND:
      //printf("CMD\n");
      //padding ( '\t', level );
      //printf(COLOR_WORD);
      //printf("%s", root->cmd->args[0]);
      //printf(COLOR_RESET);
      print_command(root->cmd);
      break;
    default:
      break;
	}
    printf ("\n");
    print_ast ( root->left, level + 1 );
  }
}