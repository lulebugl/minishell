/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:22:37 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/04 18:15:32 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "structures.h"
# include <assert.h>

# define COLOR_RESET "\x1b[0m"
# define COLOR_WORD "\e[0;35m"        // Light blue
# define COLOR_PIPE "\x1b[38;5;213m"  // Pink
# define COLOR_REDIR "\x1b[38;5;220m" // Yellow
# define COLOR_AND "\e[0;36m"
# define COLOR_OR "\e[0;36m"
# define COLOR_PAR "\e[0;32m"
# define COLOR_SPECIAL "\x1b[38;5;159m" // Cyan

void	test_arg_input(const char *input, t_data *data);
void	print_tokens_formatted(t_token *tokens);
void	debug_cmd(t_data *data, t_command *cmd);
int		debug_expander(t_command *cmd);

#endif

