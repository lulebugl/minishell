/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:02:44 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/02 17:02:45 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdbool.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"

typedef struct s_env
{
	char					*key;
	char					*value;
	struct s_env			*next;
}							t_env;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_IN,
	TOKEN_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_OPEN_PAR,
	TOKEN_CLOSE_PAR,
}							t_token_type;

typedef struct s_token_pos
{
	int						start;
	int						len;
}							t_token_pos;

typedef struct s_token
{
	t_token_type			type;
	char					*content;
	struct s_token			*next;
}							t_token;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR
}							t_node_type;

typedef struct s_redirection
{
	t_token_type			type;
	char					*filename;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_command
{
	t_list					*arg_lst;
	int						arg_count;
	t_redirection			*redirections;
	int						redir_count;
}							t_command;

typedef struct s_tree_node
{
	t_node_type				type;
	t_command				*cmd;
	struct s_tree_node		*left;
	struct s_tree_node		*right;
}							t_tree_node;

typedef struct s_exec
{
	int						stdin_backup;
	int						stdout_backup;
	int						fd_in;
	int						fd_out;
	pid_t					pid;
	pid_t					*child_pids;
	int						pipe[2];
}							t_exec;

typedef struct s_data
{
	t_env					*env;
	t_token					*tokens;
	t_tree_node				*ast;
	int						status;
	bool					print_token;
	bool					print_ast;
	bool					exec_debug;
	char					**envp;
}							t_data;

#endif

