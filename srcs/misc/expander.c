/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:04:57 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/22 17:04:59 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expander(t_data *data)
{
	t_env	*env;
	bool	expand;
	int		i;
	t_token	*tokens;
	int		start;
	char	*res;
	char	*tmp;

	tokens = data->tokens;
	env = data->env;
	if (!env)
		return (0);
	while (tokens)
	{
		if (tokens->content)
		{
			i = 0;
			printf("Token -> %s\n", tokens->content);
			expand = true;
			if (tokens->content[i] == '\'')
			{
				expand = false;
				i++;
			}
			else if (tokens->content[i] == '\'')
				i++;
			while (tokens->content[i] && tokens->content[i] != '$')
				i++;
			if (tokens->content[i + 1] && tokens->content[i] == '$'
				&& expand == true)
			{
				start = i + 1;
				while ((ft_isalnum((int)tokens->content[i])
					|| tokens->content[i] == '_') && tokens->content[i] != '\"')
					i++;
				tmp = ft_strndup(tokens->content + start, i - start);
				printf("key -> %s\n", tmp);
				res = env_get_value(env, tmp);
				printf("value -> %s\n", res);
			}
			else
				i++;
		}
		tokens = tokens->next;
	}
	return (0);
}

