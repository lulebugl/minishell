/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:58:41 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/22 17:52:29 by maxweert         ###   ########.fr       */
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
int		ft_unset(t_env *env, char **args);
int		ft_export(t_env *env, char **args);

// ENV

void	env_init(t_env **env, char **env_arr);
void	env_free(t_env *env);
t_env	*env_create_elem(char *key, char *value);
void	env_add_key(t_env **env, char *key, char *value);
char	*env_get_value(t_env *env, char *key);
int		env_key_exists(t_env *env, char *key);
void	env_update_key(t_env *env, char *key, char *value);
char	*env_key_from_str(char *str);
char	*env_value_from_str(char *str);
#endif
