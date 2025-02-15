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

/*
 * Function: expand_tilde
 * ----------------------------
 *	if the token's first character is a tilde ('~') and is the only character or
 *	the next character is '/', replace the tilde with the $HOME variable. 
 *	returns 0 if successful or conditions not met, and 1 on error
 */
int	expand_tilde(t_data *data, t_list *arg, bool expand)
{
	char	*value;
	char	*content;
	
	content = (char *)arg->content;
	if (!expand || !arg || !content || !content[0])
		return (0);
	if (content[0] != '~' || (content[0] == '~'
			&& content[1] && content[1] != '/'))
		return (0);
	value = env_get_value(data->env, "HOME");
	if (!value)
	{
		if (errno)
			return (1);
		arg->content = replace_key(content, "", 1, 0);
		if (!content)
			return (1);
		return (0);
	}
	arg->content = replace_key(content, value, 1, 0);
	if (!content)
		return (1);
	return (0);
}

/*
 * Function: remove_quotes
 * ----------------------------
 *	Remove the quotes at the start and end of the "word"
 *	Free the original string
 * 	Return the new string if no error occured, otherwise NULL
 */
char	*remove_quotes(char *str, bool *expand)
{
	char	*trimmed;

	if (!str)
		return (NULL);
	if ((!*str) || (*str && (*str != '\'' && *str != '\"')))
		return (str);
	if (*str == '\'')
		*expand = false;
	trimmed = ft_substr(str, 1, ft_strlen(str) - 2);
	if (!trimmed)
		return (NULL);
	free(str);
	return (trimmed);
}

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
	bool	quoted;

	quoted = false;
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


/************ old ***********/

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
	str = replace_key(str, value, start, ft_strlen(key));
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
	str = handle_env_value(str, value, key, start);
	if (!str)
		return (free(key), NULL);
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
		str = handle_env_var(str, data->env, &i);
		if (!str)
			return (NULL);
		argv = str;
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
			// argv[i] = expand_tilde();
			argv[i] = expand_arg(data, argv[i], expand);
			if (!argv[i])
				err_and_exit(data);
		}
		i++;
	}
	return (0);
}