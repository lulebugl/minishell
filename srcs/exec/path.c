/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:55:02 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/04 18:55:21 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*try_path(char *str, char *env)
{
	int		i;
	char	**path;
	char	*valid_path;
	char	*tmp;

	i = -1;
	valid_path = NULL;
	path = ft_split(env, ':');
	if (!path)
		return (NULL);
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		valid_path = ft_strjoin_n_free(tmp, str);
		if (!valid_path)
			return (ft_free_tab(path), NULL);
		if (access(valid_path, F_OK) == 0)
			break ;
		free(valid_path);
		valid_path = NULL;
	}
	ft_free_tab(path);
	return (valid_path);
}

char	*get_path(char *str, t_env *env)
{
	int		i;
	t_env	*curr;

	i = 0;
	curr = env;
	if (!str)
		return (NULL);
	while (curr)
	{
		if (curr->key && ft_strncmp(curr->key, "PATH", 4) == 0)
			return (try_path(str, curr->value));
		curr = curr->next;
	}
	return (NULL);
}
