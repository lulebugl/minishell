/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:57:44 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/27 19:57:48 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "minishell.h"

typedef enum e_node_type
{
	NODE_COMMAND, // Simple command (ls, echo, etc.)
	NODE_PIPE     // Pipe between commands
}						t_node_type;

// Command structure to hold command name and args
typedef struct s_command
{
	char **args;   // Array of strings (command + args)
	int arg_count; // Number of arguments
}						t_command;

typedef struct s_ast_node
{
	t_node_type			type;
	void *data; // Points to command data if type is NODE_COMMAND
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	int					id;
}						t_ast_node;

// Function prototypes
t_ast_node				*build_ast(t_token *tokens);
void					print_ast(t_ast_node *node, int level);
void					free_ast(t_ast_node *node);

#endif
