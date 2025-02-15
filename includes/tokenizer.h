/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:54:03 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/30 22:35:07 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# define ERR_MSG_QUOTES "unclosed quotes.\n"
# define ERR_MSG_SYNTAX "syntax error : "

# define ERR_SYNTAX 2

typedef struct s_data	t_data;

# include "structures.h"

int						tokenize_input(const char *s, t_token **tokens,
							t_data *data);
void					msg_custom_err(char *msg, char *details);
int						handle_quotes(const char *s, int *pos, char type,
							t_token **tokens);
int						handle_io(const char *s, int *pos,
							t_token **tokens);
int						handle_pipes(const char *s, int *pos, t_token **tokens,
							t_data *data);
int						handle_parenthesis(const char *s, int *pos,
							t_token **tokens);
int						handle_logical_and(const char *s, int *pos,
							t_token **tokens);

int						validate_prompt(t_token *token);

/* utils */
int						add_token(t_token **tokens, const char *prompt,
							t_token_pos pos, t_token_type type);
void					push_token(t_token **lst, t_token *node);
t_token					*new_token(char *content, t_token_type type);
void					clear_tokens(t_token **tokens);
int						token_is_redir(t_token *token);

#endif