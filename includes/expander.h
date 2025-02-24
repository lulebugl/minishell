/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 20:43:49 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/20 19:12:27 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "structures.h"

int		expand_tilde(t_data *data, t_list *arg);
int		expand_arg_recursive(t_data *data, t_list *args, bool expand);
int		handle_env_var(t_list *arg_node, t_env *env, int *i);
int		expander(t_data *data, t_command *cmd);
int		separate_expanded(t_data *data, t_list *args);
char	*replace_key(char *str, char *replace, int start, int key_len);
int		remove_quotes(t_data *data, t_list *args);
int		expand_wildcard(t_list **current);
int		expand_keys(t_data *data, t_list *args);
char	*replace_substring(char *str, size_t start, size_t len, char *replace);

/* utils */
int		del_empty_args(t_list **head, t_list *node_to_delete);
int		only_empty_arg(char *arg);
bool	skip_in_single_quote(char *str, int *i);

#endif

