/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:57:44 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/30 23:32:34 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "structures.h"

t_tree_node					*new_tree(t_data *data, t_token **token);
t_command					*get_command(t_token **token);
t_redirection				*get_redirections(t_token **token);
int							count_redirections(t_redirection *root);
void						free_command(t_command *cmd);
void						free_redirections(t_redirection *root);
void						free_tree(t_tree_node *root);
void						print_ast(t_tree_node *root, int level);
void						print_ast_lucas(t_tree_node *node, int level);

#endif
