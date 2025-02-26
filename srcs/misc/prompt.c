/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:49:54 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/22 15:49:55 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_shortened_path(const char *path)
{
	char	*home;
	size_t	home_len;
	char	*shortened;

	home = getenv("HOME");
	if (!home)
		return (ft_strdup(path));
	home_len = ft_strlen(home);
	if (ft_strncmp(path, home, home_len) == 0)
	{
		shortened = malloc(ft_strlen(path) - home_len + 2);
		if (!shortened)
			return (NULL);
		shortened[0] = '~';
		ft_strcpy(shortened + 1, (char *)path + home_len);
		return (shortened);
	}
	return (ft_strdup(path));
}

void	print_details(void)
{
	char	curr[PATH_MAX];
	char	*username;
	char	*short_path;
	char	*shlvl;
	char	*git_branch;

	if (!getcwd(curr, PATH_MAX))
		return ;
	username = getenv("USER");
	short_path = get_shortened_path(curr);
	shlvl = getenv("SHLVL");
	git_branch = get_git_branch();
	if (!short_path)
		return ;
	printf("%s%s┌─[%s%s%s]", BOLD, BLUE, MAGENTA, short_path, BLUE);
	if (shlvl)
		printf("%s[%s%s%s]", BLUE, YELLOW, shlvl, BLUE);
	if (git_branch)
	{
		printf("%s[%s%s%s]", BLUE, CYAN, git_branch, BLUE);
		free(git_branch);
	}
	printf("\n");
	free(short_path);
}

// void	print_details(void)
// {
// 	char	curr[PATH_MAX];
// 	char	*short_path;
// 	char	*git_branch;

// 	if (!getcwd(curr, PATH_MAX))
// 		return ;
// 	short_path = get_shortened_path(curr);
// 	if (!short_path)
// 		return ;
// 	printf("%s%s%s", MAGENTA, short_path, RESET);
// 	git_branch = get_git_branch();
// 	if (git_branch)
// 	{
// 		printf(" %s%s%s", DGRAY, git_branch, RESET);
// 		free(git_branch);
// 	}
// 	printf("\n");
// 	free(short_path);
// }