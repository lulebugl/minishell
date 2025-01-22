/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 03:32:02 by maxweert          #+#    #+#             */
/*   Updated: 2025/01/22 03:41:16 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// SI PAS ARG -> PRINT ENV ORDRE ALPHA
// PLUSIEURS ARGS ET AU MOINS 1 ERREUR -> RETURN 1
// ARG COMMENCE PAR CHIFFRE -> not an identifier
// ARG MAL FORMATTE -> not valid in this context

int	export(t_env *env, char **args)
{
	int	i;
	int	err;

	err = 0;

	i = 0;
	if (err)
		return (ERROR);
	return (SUCCESS);
}