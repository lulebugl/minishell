/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expanded.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 20:35:26 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/20 20:03:05 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*create_new_arg(char *str, size_t start, size_t len)
{
	t_list	*node;
	char	*word;

	word = ft_substr(str, start, len);
	if (!word)
		return (NULL);
	node = ft_lstnew(word);
	if (!node)
	{
		free(word);
		return (NULL);
	}
	return (node);
}

static t_list	*insert_new_arg(t_list *args, t_list *new, t_list *next,
		int start)
{
	if (!args)
		return (NULL);
	if (start == 0)
	{
		free(args->content);
		args->content = new->content;
		free(new);
		return (args);
	}
	else
	{
		args->next = new;
		new->next = next;
		return (new);
	}
}

static void	split_expanded(t_data *data, t_list *args)
{
	char	*str;
	t_list	*next;
	t_list	*new;
	int		i;
	int		start;

	if (!args || !args->content)
		return ;
	next = args->next;
	str = ft_strdup(args->content);
	if (!str)
		err_and_exit(data);
	i = 0;
	while (str[i])
	{
		start = i;
		while (str[i] && str[i] != ' ')
			i++;
		new = create_new_arg(str, start, i - start);
		if (!new)
			return (free(str), err_and_exit(data));
		args = insert_new_arg(args, new, next, start);
		i += (str[i] == ' ');
	}
	return (free(str));
}

t_list	*lst_get_last_and_prev(t_list *curr, t_list **prev, t_list *next)
{
	while (curr && curr->next)
	{
		*prev = curr;
		curr = curr->next;
	}
	curr->next = next;
	return (curr);
}

/*
 * Function: split_expanded_arguments
 * ----------------------------
 * After parameter expansion, some arguments might contain spaces
 * from expanded environment variables. This function splits those.
 */
int	split_expanded_arguments(t_data *data, t_command *cmd)
{
	t_list	*curr;
	t_list	*next;
	t_list	*prev;

	curr = cmd->arg_lst;
	prev = NULL;
	while (curr)
	{
		next = curr->next;
		if (curr->content && has_unquoted_space(curr->content))
		{
			split_expanded(data, curr);
			if (!prev)
				cmd->arg_lst = curr;
			else
				prev->next = curr;
			curr = lst_get_last_and_prev(curr, &prev, next);
		}
		else
			prev = curr;
		curr = next;
	}
	return (SUCCESS);
}

