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
}					t_token_type;

typedef struct s_list t_token;

int tokenize_input(const char *s, t_token **token);

// typedef struct s_token
// {
// 	// int				type;
// 	void			*content;
// 	struct s_token	*next;
// }					t_token;

#endif

