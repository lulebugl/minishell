/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:57:44 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/30 23:09:12 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "minishell.h"

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR
}	t_node_type;

typedef struct s_redirection
{
	t_token_type			type;
	char					*filename;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_command
{
	char			**args;
	int				arg_count;
	t_redirection	*redirections;
	int				redir_count;
}	t_command;

typedef struct s_tree_node
{
	t_node_type			type;
	t_command			*cmd;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree_node;

t_tree_node		*new_tree(t_data *data, t_token **token);
t_tree_node		*new_node(t_node_type type);
t_command		*get_command(t_token **token);
t_redirection	*get_redirections(t_token **token);
int				count_redirections(t_redirection *root);
void			free_command(t_command *cmd);
void			free_redirections(t_redirection *root);
void			free_tree(t_tree_node *root);
void			print_ast(t_tree_node *root, int level);

#endif