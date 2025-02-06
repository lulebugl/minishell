/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 00:52:38 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/07 00:56:42 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <fnmatch.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void		find_matching_paths(const char *base_path, const char *pattern);

static int	match(const char *str_wildcard, const char *to_check)
{
	if (*str_wildcard == '\0' && *to_check == '\0')
		return (1);
	if (*str_wildcard == '*')
	{
		while (*(str_wildcard + 1) == '*')
			str_wildcard++;
	}
	if (*str_wildcard == '*' && *(str_wildcard + 1) != '\0'
		&& *to_check == '\0')
		return (0);
	if (*str_wildcard == *to_check)
		return (match(str_wildcard + 1, to_check + 1));
	if (*str_wildcard == '*')
		return (match(str_wildcard + 1, to_check) || match(str_wildcard,
				to_check + 1));
	return (0);
}

static void	process_entry(const char *base_path, const char *entry_name,
		const char *pattern, const char *remaining_pattern)
{
	char		full_path[1024];
	struct stat	statbuf;

	memset(full_path, 0, 1024);
	strcat(full_path, base_path);
	strcat(full_path, "/");
	strcat(full_path, entry_name);
	if (match(pattern, entry_name))
	{
		if (remaining_pattern == NULL)
			printf("%s\n", full_path);
		else if (stat(full_path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
			find_matching_paths(full_path, remaining_pattern);
	}
}

void	find_matching_paths(const char *base_path, const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	char			segment[1024];
	const char		*slash;

	slash = strchr(pattern, '/');
	dir = opendir(base_path);
	if (!dir)
	{
		perror("opendir");
		return ;
	}
	if (slash)
	{
		strncpy(segment, pattern, slash - pattern);
		segment[slash - pattern] = '\0';
		pattern = slash + 1;
	}
	else
	{
		strcpy(segment, pattern);
		pattern = NULL;
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		process_entry(base_path, entry->d_name, segment, pattern);
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
	find_matching_paths(".", argv[1]);
	return (EXIT_SUCCESS);
}
