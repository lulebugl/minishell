/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:07:21 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/27 16:16:39 by maxweert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	long	res;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (sign * (int)res);
}
