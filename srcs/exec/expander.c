/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:07:07 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/13 21:07:08 by llebugle         ###   ########.fr       */
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

int	update_args(t_data *data, t_list *args)
{
	char	*arg;
	int		i;
	int		start;
	t_list	*next;
	t_list	*new;

	i = 0;
	if (!args)
		return (0);
	next = args->next;
	arg = ft_strdup((char *)args->content);
	if (!arg)
		err_and_exit(data);
	while (arg[i])
	{
		start = i;
		while (arg[i] && arg[i] != ' ')
			i++;
		new = ft_lstnew(ft_substr(arg, start, i - start));
		if (!new)
		{
			free(arg);
			err_and_exit(data);
		}
		if (start == 0)
		{
			free(args->content);
			args->content = new->content;
			free(new);
		}
		else
		{
			args->next = new;
			new->next = next;
			args = new;
		}
		if (arg[i] == ' ')
			i++;
	}
	free(arg);
	return (0);
}

int	expand_args(t_data *data, t_command *cmd)
{
	bool	expand;
	int		quoted;
	t_list	*args;
	char	*arg;
	t_list	*next;

	args = cmd->arg_lst;
	while (args)
	{
		next = args->next;
		arg = args->content;
		if (arg)
		{
			expand = true;
			if (ft_strcmp(arg, "\"\"") == 0 || ft_strcmp(arg, "\'\'") == 0)
			{
				args = args->next;
				continue ;
			}
			args->content = remove_quotes(arg, &expand, &quoted);
			if (!arg)
				return (1);
			if (expand_tilde(data, args, expand))
				return (1);
			if (expand_arg_recursive(data, args, expand))
				return (1);
			if (!del_empty_args(&cmd->arg_lst, args))
			{
				// reading_quote();
			}
			if (!quoted)
				update_args(data, args);
		}
		args = next;
	}
	debug_expander(cmd);
	cmd->arg_count = ft_lstsize(cmd->arg_lst);
	return (0);
}

