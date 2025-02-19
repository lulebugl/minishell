/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_recursive.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 20:24:55 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/19 20:24:56 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_exit_status(t_data *data, t_list *arg, int *i)
{
	char	*value;
	int		start;

	start = ++(*i);
	value = ft_itoa(data->exit_code);
	if (!value)
		return (1);
	arg->content = replace_key((char *)arg->content, value, start, 2);
	free(value);
	if (!arg->content)
		return (1);
	return (0);
}

static int	handle_env_value(t_list *arg, char *value, char *key, int start)
{
	if (!value)
	{
		if (errno)
			return (1);
		arg->content = replace_key((char *)arg->content, "", start,
				ft_strlen(key));
		if (!arg->content)
			return (1);
		return (0);
	}
	arg->content = replace_key((char *)arg->content, value, start,
			ft_strlen(key));
	if (!arg->content)
		return (1);
	return (0);
}

int	handle_env_var(t_list *arg_node, t_env *env, int *i)
{
	char	*key;
	char	*value;
	int		start;
	char	*arg;

	start = ++(*i);
	arg = (char *)arg_node->content;
	while ((ft_isalnum((int)arg[*i]) || arg[*i] == '_') && arg[*i] != '\"')
		(*i)++;
	key = ft_strndup(arg_node->content + start, *i - start);
	if (!key)
		return (1);
	value = env_get_value(env, key);
	if (handle_env_value(arg_node, value, key, start))
		return (free(key), 1);
	free(key);
	return (0);
}

int	expand_arg_recursive(t_data *data, t_list *args, bool expand)
{
	int		i;
	char	*arg;

	arg = (char *)args->content;
	i = 0;
	if (!arg)
		return (1);
	while (arg[i] && arg[i] != '$')
		i++;
	if (arg[i] == '$' && arg[i + 1] && arg[i + 1] == '?' && expand)
	{
		if (handle_exit_status(data, args, &i))
			return (1);
		return (expand_arg_recursive(data, args, expand));
	}
	else if (arg[i] && arg[i + 1] && arg[i] == '$' && expand)
	{
		if (handle_env_var(args, data->env, &i))
			return (1);
		return (expand_arg_recursive(data, args, expand));
	}
	if (arg[i] && arg[i + 1] != '\0' && expand)
		return (expand_arg_recursive(data, args, expand));
	return (0);
}
