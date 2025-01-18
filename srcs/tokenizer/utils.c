/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:01:18 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/18 17:01:20 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_custom_err(char *msg, char *details)
{
	ft_printf_fd(STDERR_FILENO, "minishell : ");
	if (details)
		ft_printf_fd(STDERR_FILENO, details);
	if (msg)
		ft_printf_fd(STDERR_FILENO, msg);
}