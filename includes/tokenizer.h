/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:54:03 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/16 17:54:18 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# define ERR_MSG_QUOTES "Unclosed quotes.\n"
# define ERR_MSG_SYNTAX "syntax error : "

# define ERR_SYNTAX 256

typedef struct s_data	t_data;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_IN,
	TOKEN_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
}						t_token_type;

// typedef struct s_list	t_token;

typedef struct s_token
{
	t_token_type		type;
	char				*content;
	struct s_token		*next;
}						t_token;

int						tokenize_input(const char *s, t_token **tokens,
							t_data *data);
void					msg_custom_err(char *msg, char *details);
int						handle_quotes(const char *s, int *pos, char type,
							t_token **tokens, t_data *data);
int						handle_io(const char *s, int *pos, char type,
							t_token **tokens, t_data *data);
int						handle_pipes(const char *s, int *pos, t_token **tokens, t_data *data);

/* utils */
void					push_token(t_token **lst, t_token *node);
t_token					*new_token(char *content, t_token_type type);

#endif

