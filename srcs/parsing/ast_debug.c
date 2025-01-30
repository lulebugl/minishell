/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:03:30 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/30 22:38:26 by maxweert         ###   ########.fr       */
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
      printf(COLOR_WORD);
      printf("%s", root->cmd->args[0]);
      printf(COLOR_RESET);
      break;
      break;
    default:
      break;
	}
    printf ("\n");
    print_ast ( root->left, level + 1 );
  }
}