/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:32:24 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/08 18:57:44 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_n_free(char *s1, char const *s2)
{
	char	*new;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		len = ft_strlen(s2);
	else
		len = ft_strlen(s1) + ft_strlen(s2);
	new = malloc(sizeof(char) * len + 1);
	if (!new)
		return (NULL);
	i = -1;
	while (s1[++i] && i < len)
		new[i] = s1[i];
	j = -1;
	while (s2[++j] && i + j < len)
		new[i + j] = s2[j];
	new[i + j] = '\0';
	if (s1)
		free(s1);
	return (new);
}

static char	*extract_line(char *str)
{
	char	*new;
	char	*endl;
	size_t	end;

	end = 0;
	if (!str)
		return (NULL);
	endl = ft_strchr(str, '\n');
	if (endl == NULL)
		return (str);
	end = ft_strlen(str) - ft_strlen(endl);
	new = ft_substr(str, 0, end + 1);
	return (new);
}

static char	*read_and_append(int fd, char *current)
{
	char	*buffer;
	int		ret;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	ret = 1;
	while (ret > 0 && (!current || !ft_strchr(current, '\n')))
	{
		if (!current)
			current = ft_calloc(1, sizeof(char));
		if (!current)
			return (free(buffer), NULL);
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buffer);
			return (free(current), NULL);
		}
		buffer[ret] = '\0';
		current = ft_strjoin_n_free(current, buffer);
		if (!current)
			return (NULL);
	}
	return (free(buffer), current);
}

char	*remove_line_read(char *current)
{
	char	*new;
	size_t	start;
	char	*endl;

	if (!current)
		return (NULL);
	endl = ft_strchr(current, '\n');
	if (!endl)
		return (NULL);
	start = ft_strlen(current) - ft_strlen(ft_strchr(current, '\n')) + 1;
	new = ft_substr(current, start, ft_strlen(current));
	free(current);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*current[FD_MAX];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1 || fd >= FD_MAX)
		return (NULL);
	current[fd] = read_and_append(fd, current[fd]);
	if (!current[fd])
		return (NULL);
	if (*current[fd] == '\0')
	{
		free(current[fd]);
		current[fd] = NULL;
		return (NULL);
	}
	line = extract_line(current[fd]);
	if (!line)
	{
		current[fd] = NULL;
		return (NULL);
	}
	current[fd] = remove_line_read(current[fd]);
	return (line);
}
