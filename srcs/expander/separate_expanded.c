/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 20:35:26 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/19 20:35:28 by llebugle         ###   ########.fr       */
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

int	separate_expanded(t_data *data, t_list *args)
{
	char	*str;
	t_list	*next;
	t_list	*new;
	int		i;
	int		start;

	printf("%p\n", args);
	printf("%s\n", (char *)args->content);
	if (!args || !args->content)
		return (0);
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
			return (free(str), err_and_exit(data), 1);
		args = insert_new_arg(args, new, next, start);
		i += (str[i] == ' ');
	}
	return (free(str), 0);
}
