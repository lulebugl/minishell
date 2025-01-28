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
	NODE_COMMAND,  // Simple command
	NODE_PIPELINE, // Pipeline of commands
	NODE_AND,      // &&
	NODE_OR        // ||
}						t_node_type;

typedef struct s_redirection
{
	t_token_type		type;
	char *filename; // File to redirect to/from or heredoc delimiter
}						t_redirection;

typedef struct s_command
{
	char **args; // Command and its arguments
	int					arg_count;
	t_redirection		**redirects;
	int					redir_count;
}						t_command;

typedef struct s_ast_node
{
	t_node_type			type;
	struct s_ast_node	*left;
	struct s_ast_node **pipeline; // Array of commands in pipeline
	int pipe_count;               // Number of commands in pipeline but why??
	struct s_ast_node	*right;
	t_command			*cmd;
}						t_ast_node;

// Function prototypes
t_ast_node				*create_node(t_node_type type);
t_ast_node				*create_command_node(char **args, int arg_count);
void					print_ast(t_ast_node *node, int level);
void					free_ast(t_ast_node *node);
t_ast_node				*parse_tokens(t_data *data, t_token *tokens);
t_ast_node				*parse_tokens_r(t_data *data, t_token *start,
							t_token *end);
t_node_type				token_to_node_type(t_token_type type);
t_token					*find_last_operator(t_token *start, t_token *end,
							t_token_type type);
t_ast_node				*ast_create_command(char **args, int arg_count);
void					ast_add_redirection(t_command *cmd,
							t_redirection *redir);
t_ast_node				*create_command(t_token *token);

#endif

