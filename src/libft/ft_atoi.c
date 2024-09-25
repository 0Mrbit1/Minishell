/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 08:23:57 by acharik           #+#    #+#             */
/*   Updated: 2023/11/24 13:01:54 by acharik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	ft_power(size_t number, size_t power)
{
	size_t	result;

	result = 1;
	while (power--)
	{
		result = result * number;
	}
	return (result);
}

static int	calculate_number(const char *str, int i)
{
	int	len;
	int	number;
	int	start;

	len = 0;
	number = 0;
	start = i;
	while (str[i] >= '0' && str[i] <= '9')
	{
		len++;
		i++;
	}
	i = start;
	while (len)
	{
		number = number + (str[i] - '0') * ft_power(10, --len);
		i++;
	}
	return (number);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
	{
		i++;
	}
	if (!(str[i] >= '0' && str[i] <= '9'))
	{
		return (0);
	}
	return (sign * calculate_number(str, i));
}
