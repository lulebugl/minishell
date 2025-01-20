/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:58:41 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/20 20:07:54 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "tokenizer.h"

/* for debug */
# include "debug.h"

/* standard */
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define PROMPT "\x1b[38;5;87mminishell > \033[0m"

/* color codes */
# define PURPLE "\e[0;35m"
# define CYAN "\e[0;36m"
# define RED "\e[0;31m"
# define GREEN "\e[0;32m"
# define RESET "\033[0m"

/* color codes high intensity */
# define HI_CYAN "\e[1;96m"

typedef struct s_data
{
	t_list	*env;
	t_token	*tokens;
	int		status;
}			t_data;

void		init_signals(void);

#endif
