/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:07:07 by llebugle          #+#    #+#             */
/*   Updated: 2025/02/13 21:07:08 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// staticc int	expander(t_data *data)
// {
// 	bool	expand;
// 	t_token	*token;

// 	token = data->tokens;
// 	while (token)
// 	{
// 		if (token->content)
// 		{
// 			expand = true;
// 			token->content = remove_quotes(token->content, &expand);
// 			if (!token->content)
// 				return (1);
// 			if (expand_token_recursive(data, token, expand))
// 				return (1);
// 			if (expand_tilde(data, token, expand))
// 				return (1);
// 		}
// 		token = token->next;
// 	}
// 	return (0);
// }


// void	expand_args(t_data *data, t_command *cmd)
// {
// 	t_list	*tmp;

// 	tmp = cmd->arg_lst;
// 	if (expander_new(data, tmp, cmd->arg_count))
// 		// probably a lot of leaks,	will need to rewrite it i think
// 		err_and_exit(data);
// }
