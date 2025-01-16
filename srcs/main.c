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

int exec_prompt(const char *prompt)
{
	if (ft_strncmp(prompt, "exit", 5) == 0)
		exit(0);
	return (0);
}

int launch_program()
{
	while (true)
	{
		char *rl;
		
		rl = readline(PROMPT);
		if (!rl)
			exit(1);
		exec_prompt(rl);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	launch_program();
	return (0);
}
