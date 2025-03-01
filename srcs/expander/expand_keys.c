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

static char	*key_not_found(t_data *data, char *str, int start, int len)
{
	str = replace_substring(str, start, len + 1, "");
	if (!str)
		err_and_exit(data);
	return (str);
}

static char	*expand_var(t_data *data, char *str, int *i)
{
	char	*value;
	int		len;
	int		start;
	char	*key;

	start = *i + 1;
	len = 0;
	while (str[start + len] && (ft_isalnum(str[start + len]) || str[start
			+ len] == '_'))
		len++;
	key = ft_substr(str, start, len);
	if (!key)
		err_and_exit(data);
	value = env_get_value(data->env, key);
	free(key);
	if (!value)
		return (key_not_found(data, str, *i, len));
	str = replace_substring(str, *i, len + 1, value);
	(*i) += ft_strlen(value);
	if (!str)
		err_and_exit(data);
	return (str);
}

char	*expand_str(t_data *data, char *arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
	{
		if (skip_in_single_quote(arg, &i) == true)
			continue ;
		if (arg[i] == '$' && arg[i + 1] == '?')
		{
			arg = expand_status(data, arg, &i);
			if (!arg)
				err_and_exit(data);
			continue ;
		}
		if (arg[i] == '$' && (ft_isalpha(arg[i + 1]) || arg[i + 1] == '_'))
		{
			arg = expand_var(data, arg, &i);
			if (!arg)
				err_and_exit(data);
			continue ;
		}
		if (arg[i])
			i++;
	}
	return (arg);
}

int expand_keys(t_data *data, t_list **args_ptr)
{
    t_list *curr;
    t_list *prev = NULL;

    if (!args_ptr || !*args_ptr)
        return (1);
    
    curr = *args_ptr;
    
    while (curr)
    {
        t_list *next = curr->next; // Save next before potential delete
        
        if (!curr->content)
        {
            prev = curr;
            curr = next;
            continue;
        }
        
        curr->content = expand_str(data, curr->content);
        if (!curr->content)
            return (1);
            
        if (ft_strcmp(curr->content, "") == 0)
        {
            // If we're deleting the head node
            if (curr == *args_ptr)
            {
                *args_ptr = next; // Update the head pointer
                free(curr->content);
                free(curr);
                curr = next;
                // prev remains NULL
            }
            else
            {
                // For non-head nodes
                prev->next = next;
                free(curr->content);
                free(curr);
                curr = next;
                // prev stays the same
            }
        }
        else
        {
            prev = curr;
            curr = next;
        }
    }
    
    return (0);
}
