/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 01:33:38 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/19 12:47:53 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	match_rec(char *pattern, char *to_check)
{
	if (*pattern == '\0' && *to_check == '\0')
		return (1);
	if (*pattern == '*')
	{
		while (*(pattern + 1) == '*')
			pattern++;
	}
	if (*pattern == '*' && *(pattern + 1) != '\0'
		&& *to_check == '\0')
		return (0);
	if (*pattern == *to_check)
		return (match_rec(pattern + 1, to_check + 1));
	if (*pattern == '*')
		return (match_rec(pattern + 1, to_check) || match_rec(pattern,
				to_check + 1));
	return (0);
}

static int	match_wildcard(char *pattern, char *to_check)
{
	if (*to_check == '.' && *pattern != '.')
		return (0);
	return (match_rec(pattern, to_check));
}

static int	ft_strcmp_case_insensitive(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && ft_tolower(s1[i]) == ft_tolower(s2[i]))
		i++;
	return (ft_tolower(s1[i]) - ft_tolower(s2[i]));
}

t_list	*find_matchs(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*matchs;

	matchs = NULL;
	dir = opendir(".");
	if (!dir)
	{
		perror("minishell: opendir");
		return (NULL);
	}
	entry = readdir(dir);
	while (entry)
	{
		if (ft_strcmp(entry->d_name, ".") && ft_strcmp(entry->d_name, "..")
			&& match_wildcard(pattern, entry->d_name))
			ft_lstadd_front(&matchs, ft_lstnew(ft_strdup(entry->d_name)));
		entry = readdir(dir);
	}
	closedir(dir);
	ft_lstsort(&matchs, &ft_strcmp_case_insensitive);
	if (!matchs)
		matchs = ft_lstnew(ft_strdup(pattern));
	return (matchs);
}
