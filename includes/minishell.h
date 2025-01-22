/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:58:41 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/22 14:57:33 by maxweert         ###   ########.fr       */
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
# include <linux/limits.h>
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

# define SUCCESS 0
# define ERROR 1

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	t_env	*env;
	t_token	*tokens;
	int		status;
}			t_data;


// SIGNALS

void		init_signals(void);

// BUILTINS

int		ft_env(t_env *env);
int		ft_pwd(void);
int		ft_unset(t_env *env, char *var);
int		ft_export(t_env *env, char **args);

// ENV

void	env_init(t_env **env, char **env_arr);
void	env_free(t_env *env);
char	*env_get_var(t_env *env, char *arg);
void	env_add(t_env **env, char *str);
t_env	*env_create_elem(char *key, char *value);

#endif
