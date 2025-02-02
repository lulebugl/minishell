/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:58:43 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/02 17:58:46 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: t_env_to_envp
 * ----------------------------
 *	Convert linked list t_env to array envp[].
 */
char	**t_env_to_envp(t_env *env)
{
	char	**envp;
	int		i;
	t_env	*curr;

	curr = env;
	i = 1;
	while (curr)
	{
		curr = curr->next;
		i++;
	}
	// envp = (char **)malloc(sizeof(char *) * len);
	ft_bzero(envp, (sizeof(char *) * i));
	if (!envp)
		return (NULL);
	curr = env;
	i = 0;
	while (curr && curr->key)
	{
		printf("before '=' \n");
		envp[i] = ft_strjoin(curr->key, "=");
		printf("after '=' \n");
		
		if (!envp[i])
			return (ft_free_tab(envp), NULL);
		printf("before 2nd\n");
		
		envp[i] = ft_strjoin_n_free(envp[i], curr->value);
		printf("after 2nd\n");
		
		// printf("%s\n", envp[i]);
		if (!envp[i])
			return (ft_free_tab(envp), NULL);
		curr = curr->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

