/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:22:37 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/16 19:22:38 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

#include <assert.h>

typedef struct s_data t_data;
typedef struct s_token t_token;

void	test_arg_input(const char *input, t_data *data);
void	print_tokens_formatted(t_token *tokens);


#endif 
