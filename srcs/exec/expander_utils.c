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
	if (content[0] != '~' || (content[0] == '~' && content[1]
			&& content[1] != '/'))
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

int only_empty_arg(t_list *arg_node, t_env *env)
{
	// int i;
	// char *s;
	
	// s = (char *)arg_node->content;
	// i = 0;
	// if (!s)
	// 	return (0);
	// if (s[i] == '$')
	// {
	// 	if (handle_env_var(arg_node, env, &i))
	// 		return (1);
	// }
	// if ((char *)arg_node->content)
	if (arg_node->content && (ft_strcmp(arg_node->content, "\"\"") == 0 || ft_strcmp(arg_node->content, "\'\'") == 0))
		return (1);
	return (0);
}

// void    del_empty_args(t_list **head)
// {
//     t_list  **curr;
//     t_list  *tmp;

//     curr = head;
//     while (*curr)
//     {
//         if (((char *)(*curr)->content)[0] == '\0')
//         {
//             tmp = *curr;
//             *curr = (*curr)->next;
//             free(tmp->content);
//             free(tmp);
//         }
//         else
//             curr = &(*curr)->next;
//     }
// }

void    del_empty_args(t_list **head, t_list *node_to_delete)
{
    t_list  **curr;
    t_list  *tmp;

    if (!head || !*head || !node_to_delete)
        return;

    curr = head;
    while (*curr && *curr != node_to_delete)
        curr = &(*curr)->next;
    
        // if (*curr && (ft_strcmp(((char *)(*curr)->content), "\"\"") == 0 || ft_strcmp(((char *)(*curr)->content), "\'\'") == 0))
    if (*curr && (*curr)->content && ((char *)(*curr)->content)[0] == 0)
    {
        tmp = *curr;
        *curr = (*curr)->next;
        free(tmp->content);
        free(tmp);
    }
}