/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 00:52:38 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/11 17:27:05 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <fnmatch.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

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

int match_wildcard(char *pattern, char *to_check)
{
	if (*to_check == '.' && *pattern != '.')
		return (0);
	return (match_rec(pattern, to_check));
}

void	find_matchs(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	
	dir = opendir(".");
	if (!dir)
	{
		perror("minishell: opendir");
		return ;
	}
	entry = readdir(dir);
	while (entry)
	{
		if (match_wildcard(pattern, entry->d_name))
			printf("%s\n", entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <pattern>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	find_matchs(argv[1]);
	return (EXIT_SUCCESS);
}
