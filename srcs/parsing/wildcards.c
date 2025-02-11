/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 01:33:38 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/11 17:25:41 by maxweert         ###   ########.fr       */
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
		return (match(pattern + 1, to_check + 1));
	if (*pattern == '*')
		return (match(pattern + 1, to_check) || match(pattern,
				to_check + 1));
	return (0);
}

int match_wildcard(char *pattern, char *to_check)
{
	if (*to_check == '.' && *pattern != '.')
		return (0);
	return (match_rec(pattern, to_check));
}