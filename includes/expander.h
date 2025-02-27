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
int		remove_quotes(t_list *args);
int		expand_keys(t_data *data, t_list *args);
void	expand_wildcard(t_list **current);
int		expand_wildcards(t_command *cmd);
int		split_expanded_arguments(t_data *data, t_command *cmd);
char	*replace_substring(char *str, size_t start, size_t len, char *replace);
bool	skip_in_single_quote(char *str, int *i);
int		is_quote(int c);
int		expander(t_data *data, t_command *cmd);
bool	has_unquoted_space(const char *str);
int		is_dir(char *str);

#endif
