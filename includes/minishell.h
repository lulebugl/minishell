/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:58:41 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/15 18:58:44 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "tokenizer.h"

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

# define PROMPT "\e[0;36mminishell > \033[0m"

/* color codes */
# define PURPLE "\e[0;35m"
# define CYAN "\e[0;36m"
# define RED "\e[0;31m"
# define GREEN "\e[0;32m"
# define RESET "\033[0m"

/* color codes high intensity */
# define HI_CYAN "\e[1;96m"

typedef struct s_list t_token;

typedef struct s_data
{
	char 	**env;
	t_token	*token;
}			t_data;

#endif
