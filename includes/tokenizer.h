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

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	// TOKEN_ENV_VAR,       // $...
	// TOKEN_EXIT_STATUS,   // $?
	// TOKEN_EOF            // End of input
}						t_token_type;

typedef struct s_list	t_token;

int						tokenize_input(const char *s, t_token **token);
void					msg_custom_err(char *msg, char *details);
int						handle_quotes(const char *s, int *pos, char type,
							t_token **tokens);
int						handle_io(const char *s, int *pos, char type,
							t_token **tokens);
int						handle_pipes(const char *s, int *pos, t_token **tokens);

#endif

