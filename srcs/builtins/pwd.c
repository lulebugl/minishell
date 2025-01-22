/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:11:33 by maxweert          #+#    #+#             */
/*   Updated: 2025/01/22 12:10:35 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: ft_pwd
 * ----------------------------
 *	Print the current working directory.
 * 	Returns SUCCESS if the current directory could be obtained, otherwise ERORR.
 */

int	ft_pwd(void)
{
	char	curr[PATH_MAX];

	getcwd(curr, PATH_MAX);
	if (!curr)
		return (ERROR);
	printf("%s\n", curr);
	return (SUCCESS);
}
