/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharik <acharik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 10:35:55 by acharik           #+#    #+#             */
/*   Updated: 2023/11/28 05:26:57 by acharik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
char	*ft_substr(char const *s, unsigned int start, ssize_t len)
{
	char	*substr;
	ssize_t	i;
	ssize_t	j;

	if (!s)
		return (NULL);
	i = start;
	j = 0;
	if (start >= ft_strlen(s))
	{
		substr = ft_strdup("");
		return (substr);
	}
	if (len >= ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	while (j < len)
		substr[j++] = s[i++];
	substr[j] = '\0';
	return (substr);
}
