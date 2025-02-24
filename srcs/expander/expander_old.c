/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:07:07 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/20 16:40:05 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	handle_empty_quotes(t_data *data, t_list *args)
// {
// 	char	*arg;

// 	arg = args->content;
// 	if (ft_strcmp(arg, "\"\"") == 0 || ft_strcmp(arg, "\'\'") == 0)
// 	{
// 		free(args->content);
// 		args->content = ft_strdup("");
// 		if (!args->content)
// 			err_and_exit(data);
// 		return (1);
// 	}
// 	return (0);
// }

// static int expand_args(t_data *data, t_command *cmd, t_list **args, t_list **prev)
// {
//     t_list *next;
//     bool expand;
//     int quoted;

//     next = (*args)->next;
//     if (!(*args)->content)
//         return (*args = next, 0);
//     // if (handle_empty_quotes(data, *args))
//     // {
//     //     *args = next;
//     //     return (0);
//     // }
//     expand = true;
//     if (process_argument(data, *args, &expand, &quoted))
//         return (1);
//     //del_empty_args(&cmd->arg_lst, *args);
//     if (!quoted && *args)
//         separate_expanded(data, *args);
//     if (!quoted && (*args)->content && ft_strchr((*args)->content, '*'))
//         if (handle_wildcards_original(args, prev, cmd))
//             return (1);
//     return (*prev = *args, *args = next, 0);
// }


// char	*remove_quotes(t_data *data, char *str, bool *expand, int *quoted)
// {
// 	char	*trimmed;
// 	int		i;

// 	if (!str)
// 		return (NULL);
// 	*quoted = 0;
// 	trimmed = NULL;
// 	i = -1;
// 	while (str[++i])
// 	{
// 		if (str[i] == SINGLE_QUOTE)
// 		{
// 			*quoted = SINGLE_QUOTE;
// 			*expand = false;
// 			break ;
// 		}
// 		if (str[i] == DOUBLE_QUOTE)
// 		{
// 			*quoted = DOUBLE_QUOTE;
// 			break ;
// 		}
// 	}
// 	if (*quoted == 0)
// 		return (str);
// 	trimmed = str_del_all_char(str, *quoted);
// 	if (!trimmed)
// 		err_and_exit(data);
// 	return (free(str), trimmed);
// }
//
/*
 * Function: expand_tilde
 * ----------------------------
 *	if the token's first character is a tilde ('~') and is the only character or
 *	the next character is '/', replace the tilde with the $HOME variable.
 *	returns 0 if successful or conditions not met, and 1 on error
 */
// int	expand_tilde(t_data *data, t_list *arg, bool expand)
// {
// 	char	*value;
// 	char	*content;
// 	int		i;
// 	int quoted;

// 	i = 0;
// 	content = (char *)arg->content;
// 	if (!expand || !arg || !content || !content[0])
// 		return (0);
// 	if (content[i] != '~' || (content[i] == '~' && content[i + 1] && content[i
// 			+ 1] != '/'))
// 		return (0);
// 	value = env_get_value(data->env, "HOME");
// 	if (!value)
// 	{
// 		if (errno)
// 			return (1);
// 		arg->content = replace_key(content, "", 1, 0);
// 		if (!content)
// 			return (1);
// 		return (0);
// 	}
// 	arg->content = replace_key(content, value, 1, 0);
// 	if (!content)
// 		return (1);
// 	return (0);
// }

/*
 * Function: replace_key
 * ----------------------------
 *	Replace env variable in str with its value (*replace)
 *	from pos start.
 *  key_len is the len of the replaced var
 *	free the original str and returns a the new string if successful
 *	otherwise returns NULL without freeing the original str
 */
char	*replace_key(char *str, char *replace, int start, int key_len)
{
	char	*expanded;
	char	*first;
	char	*middle;
	char	*end;

	if (!str || key_len < 0 || !replace)
		return (NULL);
	first = ft_substr(str, 0, start - 1);
	if (!first)
		return (NULL);
	middle = ft_strjoin_n_free(first, replace);
	if (!middle)
		return (NULL);
	end = ft_substr(str, start + key_len, ft_strlen(str));
	if (!end)
		return (free(middle), NULL);
	expanded = ft_strjoin_n_free(middle, end);
	if (!expanded)
		return (free(end), NULL);
	free(end);
	free(str);
	return (expanded);
}
