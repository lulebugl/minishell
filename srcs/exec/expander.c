/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:04:57 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/30 22:42:15 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*replace_key(char *str, char *replace, int start, int key_len);
char		*remove_quotes(char *str, bool *expand);

static char	*handle_exit_status(t_data *data, char *str, int *i)
{
	char	*value;
	int		start;

	start = ++(*i);
	value = ft_itoa(data->status);
	if (!value)
		return (NULL);
	str = replace_key(str, value, start, 2);
	free(value);
	if (!str)
		return (NULL);
	return (str);
}

static char	*handle_env_value(char *str, char *value, char *key, int start)
{
	if (!value)
	{
		if (errno)
			return (NULL);
		str = replace_key(str, "", start, ft_strlen(key));
		if (!str)
			return (NULL);
		return (str);
	}
	printf("before replace_key = %s\n", str);
	str = replace_key(str, value, start, ft_strlen(key));
	printf("after replace_key = %s\n", str);
	if (!str)
		return (NULL);
	return (str);
}

static char 	*handle_env_var(char *str, t_env *env, int *i)
{
	char	*key;
	char	*value;
	int		start;

	start = ++(*i);
	while ((ft_isalnum((int)str[*i]) || str[*i] == '_') && str[*i] != '\"')
		(*i)++;
	key = ft_strndup(str + start, *i - start);
	if (!key)
		return (NULL);
	value = env_get_value(env, key);
	printf("before handle_env_value = %s\n", str);
	printf("value = %s\n", value);
	str = handle_env_value(str, value, key, start);
	if (!str)	
		return (free(key), NULL);
	printf("after handle_env_value = %s\n", str);
	free(key);
	return (str);
}

char	*expand_arg(t_data *data, char *argv, bool expand)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup(argv);
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '$' && str[i + 1] && str[i + 1] == '?' && expand)
	{
		str = handle_exit_status(data, str, &i); 
		if (!str)
			return (NULL);
		argv = str;
		return (expand_arg(data, str, expand));
	}
	else if (str[i] && str[i + 1] && str[i] == '$' && expand)
	{
		// printf("before str = %s\n", str);
		str = handle_env_var(str, data->env, &i);
		if (!str)
			return (NULL);
		argv = str;
		// printf("after str = %s\n", str);
		return (expand_arg(data, str, expand));
	}
	if (str[i] && str[i + 1] != '\0' && expand)
		return (expand_arg(data, str, expand));
	return (argv);
}

int	expander_new(t_data *data, char **argv, int argc)
{
	bool expand;
	int i;

	i = 0;
	while (i < argc)
	{
		if (argv[i])
		{
			expand = true;
			argv[i] = remove_quotes(argv[i], &expand);
			if (!argv[i])
				return (1);
			argv[i] = expand_arg(data, argv[i], expand);
			if (!argv[i])
				err_and_exit(data);
			// if (expand_tilde(data, str, expand))
			// 	return (NULL);
		}
		printf("argv[%d] -> %s\n", i, argv[i]);
		i++;
	}
	return (0);
}
