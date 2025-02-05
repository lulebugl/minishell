/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:57:44 by llebugle          #+#    #+#             */
<<<<<<< HEAD:includes/parser.h
/*   Updated: 2025/02/18 17:58:43 by maxweert         ###   ########.fr       */
=======
/*   Updated: 2025/02/05 16:58:36 by maxweert         ###   ########.fr       */
>>>>>>> 32c87f5 (modifs):includes/ast.h
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structures.h"

t_tree_node					*new_tree(t_data *data, t_token **token);
t_command					*get_command(t_token **token);
void						free_command(t_command *cmd);
void						free_redirections(t_redirection *root);
void						free_tree(t_tree_node *root);
void						print_ast(t_tree_node *root, int level);
void						add_redirection(t_redirection **root, t_redirection *new);
t_redirection				*new_redirection(t_token_type type, char *filename);
int							count_redirections(t_redirection *root);
int							token_is_part_of_command(t_token_type token_type);
char						**get_cmd_args_arr(t_command *cmd);
<<<<<<< HEAD:includes/parser.h
int							get_heredoc(char *eof);
=======
int							check_wildcards(char *arg);
>>>>>>> 32c87f5 (modifs):includes/ast.h

#endif
