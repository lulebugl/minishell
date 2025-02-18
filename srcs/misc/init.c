/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:45:59 by maxweert          #+#    #+#             */
/*   Updated: 2025/02/04 18:17:44 by llebugle         ###   ########.fr       */
/*   Updated: 2025/02/17 12:35:19 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

/*
 * Function: init_data
 * ----------------------------
 *	Initialize the data structure variables.
 */

void	data_init(t_data *data)
{
	data->status = 0;
}
