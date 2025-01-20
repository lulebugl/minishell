/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:56:49 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/15 18:56:56 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_prompt(const char *prompt, t_data *data)
{
	if (ft_strncmp(prompt, "exit", 5) == 0)
		exit(0);
	// test_arg_input(prompt, data);
	tokenize_input(prompt, &data->tokens, data);
	return (0);
}

int launch_program(t_data *data)
{
	while (true)
	{
		char *rl;
		
		rl = readline(PROMPT);
		if (!rl)
			exit(1);
		exec_prompt(rl, data);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data data;
	
	ft_memset(&data, 0, sizeof(t_data));
	launch_program(&data);
	return (0);
}
