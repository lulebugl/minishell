/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:37:55 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/13 19:25:28 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	ft_echo(char **args)
{
	int		i;
	int		nb_args;
	bool	newline;

	if (!args)
		return (ERROR);
	args = &args[1];
	i = 0;
	nb_args = count_args(&args[0]);
	newline = true;
	while (args[i])
	{
		if (i == 0 && ft_strcmp(args[i], "-n") == 0)
			newline = false;
		else
		{
			printf("%s", args[i]);
			if (i != nb_args - 1)
				printf(" ");
		}
		i++;
	}
	if (newline)
		printf("\n");
	return (SUCCESS);
}
