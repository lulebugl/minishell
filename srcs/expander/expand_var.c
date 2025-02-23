/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:40:28 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/23 16:40:29 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_in_single_quote(char *str, int *i)
{
	if (!str)
		return ;
	(*i)++;
	while (str[*i] && str[*i] != SINGLE_QUOTE)
		(*i)++;
	if (str[*i] == SINGLE_QUOTE)
		(*i)++;
}

static char	*expand_status(t_data *data, char *str, int *i)
{
	char	*status;
	
	status = ft_itoa(data->exit_code);
	if (!status)
		err_and_exit(data);
	str = replace_substring(str, *i, 2, status);
	free(status);
	if (!str)
		err_and_exit(data);
	(*i)++;
	return (str);
}

static char	*expand_var(t_data *data, char *str, int *i)
{
	char	*expanded;
	char	*value;
	int		len;
	int		start;
	char 	*key;
	
	start = *i + 1;
	len = 0;
	while (str[start + len] && (ft_isalnum(str[start + len]) || str[start + len] == '_'))
		len++;
	key = ft_substr(str, start, len);
	if (!key)
		err_and_exit(data);
	value = env_get_value(data->env, key);
	if (!value)
	{
		str = replace_substring(str, *i, ft_strlen(key) + 1, "");
		free(key);
		if (!str)
			err_and_exit(data);
		return (str);
	}
	str = replace_substring(str, *i, ft_strlen(key) + 1, value);
	(*i) += ft_strlen(key);
	free(key);
	free(value);
	if (!str)
		err_and_exit(data);
	return (str);
}

static char	*expand_arg(t_data *data, char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == SINGLE_QUOTE)
		{
			skip_in_single_quote(arg, &i);
			continue ;
		}
		if (arg[i] == '$' && arg[i + 1] == '?')
		{
			arg = expand_status(data, arg, &i);
			if (!arg)
				err_and_exit(data);
			continue ;
		}
		if (arg[i] == '$'  && (ft_isalpha(arg[i + 1]) || arg[i + 1] == '_'))
		{
			arg = expand_var(data, arg, &i);
			if (!arg)
				err_and_exit(data);
			continue ;
		}
		i++;
	}
	return (arg);
}

int	expand_vars(t_data *data, t_list *args)
{
	t_list	*curr;
	char	*arg;

	if (!args)
		return (0);
	curr = args;
	while (curr)
	{
		if (!curr->content)
		{
			curr = curr->next;
			continue ;
		}
		curr->content = expand_arg(data, curr->content); 
		if (!curr->content)
			return (1);
		curr = curr->next;
	}
	return (0);
}

