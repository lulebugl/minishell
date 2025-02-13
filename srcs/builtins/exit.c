/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:41:15 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/13 18:04:06 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_arg(char *arg)
{
	int	i;

	i = 0;
	if (!arg || !arg[0])
		return (0);
	while (arg[i] && ((arg[i] >= 9 && arg[i] <= 13) || arg[i] == ' '))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
 * Function: ft_exit
 * ----------------------------
 *	Exit  minishell
 *	Returns exitcode specified in args.
 * 	Returns last exitcode if no args.
 */

int	ft_exit(t_data *data, char **args)
{
	int	ret;

	ret = data->status;
	if (args && args[1])
	{
		if (!check_arg(args[1]))
		{
			ft_printf_fd(2, "exit\nminishell: exit: %s:\
					numeric argument required\n", args[1]);
			data_free(data);
			exit(2);
			return (2);
		}
		else
			ret = ft_atoi(args[1]);
	}
	if (args[1] && args[2])
	{
		ft_printf_fd(2, "exit\nminishell: exit: too many arguments\n");
		if (ret == 0)
			ret = 1;
		return (ret);
	}
	data_free(data);
	exit(ret);
	return (ret);
}
