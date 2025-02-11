/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:56:49 by llebugle          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2025/02/18 17:59:16 by maxweert         ###   ########.fr       */
=======
/*   Updated: 2025/02/05 16:48:07 by maxweert         ###   ########.fr       */
>>>>>>> 32c87f5 (modifs)
=======
/*   Updated: 2025/02/11 17:55:24 by maxweert         ###   ########.fr       */
>>>>>>> 8354aa8 (wildcards should be ok, added ft_lstsort in libft in order to sort matched wildcards)
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_prompt(const char *prompt, t_data *data)
{
	if (ft_strncmp(prompt, "exit", 5) == 0)
		return (data_free(data), exit(0), 0);
	if (ft_strcmp((char *)prompt, "token") == 0)
		data->print_token ^= 1;
	if (ft_strcmp((char *)prompt, "env") == 0)
		ft_env(data->env);
	if (tokenize_input(prompt, &data->tokens, data))
		return (clear_tokens(&data->tokens), 1);
	data->status = validate_prompt(data->tokens);
	if (data->status)
		return (clear_tokens(&data->tokens), 1);
	if (data->print_token)
		print_tokens_formatted(data->tokens);
	clear_tokens(&data->tokens);
	return (0);
}

int	launch_program(t_data *data)
{
	char	*rl;

	init_signals();
	while (true)
	{
		rl = readline(PROMPT);
		if (!rl)
			exit(1);
		add_history(rl);
		exec_prompt(rl, data);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

<<<<<<< HEAD
	(void)argc;
	(void)argv;
	ft_memset(&data, 0, sizeof(t_data));
	env_init(&data.env, envp);
	launch_program(&data);
	data_free(&data);
=======
	// ft_memset(&data, 0, sizeof(t_data));
	// env_init(&data.env, envp);
	// launch_program(&data);
	// data_free(&data);
	t_list *test;
	test = find_matchs(argv[1]);
	while (test)
	{
		printf("%s\n", (char*)test->content);
		test = test->next;
	}
>>>>>>> 8354aa8 (wildcards should be ok, added ft_lstsort in libft in order to sort matched wildcards)
	return (0);
}

