/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:41:15 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/19 16:48:25 by maxweert         ###   ########.fr       */
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
	unsigned int	ret;

	ret = data->exit_code;
	printf("exit\n");
	if (args && args[1])
	{
		if (!check_arg(args[1]))
		{
			ft_printf_fd(STDERR_FILENO, "minishell: exit: %s: \
numeric argument required\n", args[1]);
			return (ft_free_tab(args), data_free(data), exit(2), 1);
		}
		else
		{
			ret = ft_atol(args[1]);
			if (ret > 255)
				ret = ret % 256;
		}
	}
	if (args && args[1] && args[2])
	{
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
		return (ret != 0);
	}
	return (ft_free_tab(args), data_free(data), exit(ret), ret);
}
