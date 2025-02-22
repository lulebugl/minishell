/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:48:32 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/22 16:48:33 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_branch_name(char *line)
{
	char	*branch;
	char	*ref_start;
	char	*newline;

	ref_start = ft_strstr(line, "refs/heads/");
	if (!ref_start)
		return (NULL);
	branch = ft_strdup(ref_start + 11);
	if (branch)
	{
		newline = ft_strchr(branch, '\n');
		if (newline)
			*newline = '\0';
	}
	return (branch);
}

static char	*find_git_path(void)
{
	char	curr[PATH_MAX];
	char	check_path[PATH_MAX];
	char	*last_slash;
	char	*git_path;

	if (!getcwd(curr, PATH_MAX))
		return (NULL);
	ft_strcpy(check_path, curr);
	while (1)
	{
		ft_strlcat(check_path, "/.git/HEAD", PATH_MAX);
		if (access(check_path, F_OK) == 0)
			return (ft_strdup(check_path));
		ft_strcpy(check_path, curr);
		if (ft_strlen(check_path) <= 1)
			return (NULL);
		last_slash = ft_strrchr(check_path, '/');
		if (!last_slash)
			return (NULL);
		*last_slash = '\0';
		ft_strcpy(curr, check_path);
	}
}

static char	*read_git_head(char *git_head_path)
{
	int		fd;
	char	*line;
	char	*branch;

	fd = open(git_head_path, O_RDONLY);
	free(git_head_path);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	close(fd);
	if (!line)
		return (NULL);
	branch = extract_branch_name(line);
	free(line);
	return (branch);
}

char	*get_git_branch(void)
{
	char	*git_head_path;

	git_head_path = find_git_path();
	if (!git_head_path)
		return (NULL);
	return (read_git_head(git_head_path));
}
