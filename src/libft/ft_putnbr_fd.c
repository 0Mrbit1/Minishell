/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharik <acharik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 10:35:23 by acharik           #+#    #+#             */
/*   Updated: 2023/11/26 22:15:41 by acharik          ###   ########.fr       */
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

static int	ft_calculate_number_len(long int n)
{
	int	i;

	i = 1;
	n = n / 10;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	number;
	int			number_len;
	int			digit;

	number = n;
	if (fd >= 0)
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			number = -number;
		}
		number_len = ft_calculate_number_len(number);
		while (number_len)
		{
			digit = number / ft_power(10, number_len - 1);
			number = number - digit * ft_power(10, number_len - 1);
			digit = digit + '0';
			write(fd, &digit, 1);
			number_len--;
		}
	}
}
