/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:50:32 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/23 20:50:34 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_value_from_str2(char *str, t_env *env)
{
	int		i;
	char	*home;

	i = 0;
	if (!ft_strchr(str, '='))
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	i++;
	if (str[i] == '~' && (str[i + 1] == '\0' || str[i + 1] == '/'))
	{
		home = env_get_value(env, "HOME");
		if (!home)
			return (ft_strdup(&str[i]));
		if (str[i + 1] == '\0')
			return (ft_strdup(home));
		else
			return (ft_strjoin(home, str + i + 1));
	}
	return (ft_strdup(&str[i]));
}
