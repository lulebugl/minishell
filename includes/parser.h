/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:57:44 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/19 12:48:12 by maxweert         ###   ########.fr       */
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
int							token_is_part_of_command(t_token_type token_type);
char						**get_cmd_args_arr(t_command *cmd);
int							get_heredoc(char *eof);
t_list						*find_matchs(char *pattern);

#endif
