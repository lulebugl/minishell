/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 01:33:38 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/05 17:40:34 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_wildcards(char *arg)
{
	if (strchr(arg, '*'))
	{
		if (strchr(strchr(arg, '*'), '/'))
			return (-1);
		return (1);
	}
	return (0);
}

int	match(char *str_wildcard, char *to_check)
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

// // Fonction pour obtenir le répertoire à partir du chemin
// char *get_directory(char *path)
// {
//     char *dir = ft_strdup(path);
//     char *last_slash = ft_strrchr(dir, '/');

// 	dir = ft_strdup(path);
//     if (last_slash)
//         *(last_slash + 1) = '\0';
//     else 
//         ft_strcpy(dir, "./");
//     return (dir);
// }

// // Fonction pour obtenir le motif de wildcard à partir du chemin
// char *get_pattern(const char *path) {
//     char *last_slash = ft_strrchr(path, '/');

//     if (last_slash) {
//         return ft_strdup(last_slash + 1);
//     } else {
//         return strdup(path);
//     }
// }

// // Fonction pour trouver les fichiers correspondant au motif de wildcard
// void find_matches(const char *path) {
//     char *dir = get_directory(path);
//     char *pattern = get_pattern(path);
//     struct dirent *entry;
//     DIR *dp = opendir(dir);

//     if (dp == NULL) {
//         perror("opendir");
//         free(dir);
//         free(pattern);
//         return;
//     }

//     while ((entry = readdir(dp))) {
//         if (fnmatch(pattern, entry->d_name, 0) == 0) {
//             printf("%s%s\n", dir, entry->d_name);
//         }
//     }

//     closedir(dp);
//     free(dir);
//     free(pattern);
// }
