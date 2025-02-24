/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:58:41 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/20 17:06:44 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "tokenizer.h"

/* for debug */
# ifndef DEBUG
#  define DEBUG false
# endif

extern int	g_sig;

# include "debug.h"
# include "exec.h"
# include "expander.h"
# include "parser.h"
# include "structures.h"
# include "tokenizer.h"

/* standard */
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define PROMPT "\x1b[38;5;87mminishell > \033[0m"
# define PROMPT2 "\033[34m└─➤ \033[0m"
# define PROMPT3 "\033[35m> \033[0m"

/* color codes */
# define BOLD "\033[1m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define DGRAY "\033[90m"
# define RESET "\033[0m"

/* color codes high intensity */
# define HI_CYAN "\e[1;96m"

# define SUCCESS 0
# define ERROR 1

// DATA

void		data_init(t_data *data);
void		data_free(t_data *data);
void		reset_data(t_data *data);

// SIGNALS

void		init_signals(void);
void		reset_sigquit(void);
void		sigint_handler(int sig);
void		sigquit_handler(int sig);

// BUILTINS

int			ft_env(t_env *env);
int			ft_pwd(void);
int			ft_unset(t_env *env, char **args);
int			ft_export(t_env *env, char **args);
int			ft_echo(char **args);
int			ft_exit(t_data *data, char **args);
int			ft_cd(t_env *env, char **args);

// ENV

void		env_init(t_env **env, char **env_arr);
void		env_free(t_env *env);
void		free_str_arr(char **strs);
t_env		*env_create_elem(char *key, char *value);
void		env_add_key(t_env **env, char *key, char *value);
char		*env_get_value(t_env *env, char *key);
int			env_key_exists(t_env *env, char *key);
void		env_update_key(t_env *env, char *key, char *value);
char		*env_key_from_str(char *str);
char		*env_value_from_str(char *str);

// ERROR

void		msg_unexpected_token(char *str);
void		msg_custom_err(char *msg, char *details);
void		err_and_exit(t_data *data);

// MISC
void		print_details(void);
char		*get_git_branch(void);
t_list		*del_node_and_join(t_list **head, t_list *node_to_delete);

#endif

