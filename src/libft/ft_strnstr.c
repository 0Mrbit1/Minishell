/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharik <acharik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 10:35:45 by acharik           #+#    #+#             */
/*   Updated: 2023/11/29 11:34:08 by acharik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	li_len;
	size_t	i;

	if (!(*little))
	{
		return ((char *)big);
	}
	i = 0;
	li_len = ft_strlen(little);
	while (big[i])
	{
		if (ft_strncmp(&big[i], little, li_len) == 0)
		{
			if (i + li_len > len)
			{
				return (NULL);
			}
			return ((char *)&big[i]);
		}
		i++;
	}
	return (0);
}
