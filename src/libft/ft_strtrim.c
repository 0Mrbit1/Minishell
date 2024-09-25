/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 10:35:53 by acharik           #+#    #+#             */
/*   Updated: 2023/11/24 13:19:15 by acharik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	should_be_trimmed(const char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

static size_t	get_start(const char *s1, const char *set)
{
	size_t	start;

	start = 0;
	while (s1[start] && should_be_trimmed(s1[start], set))
	{
		start++;
	}
	return (start);
}

static size_t	get_end(const char *s1, const char *set, size_t start)
{
	size_t	trim_str_end;

	trim_str_end = start;
	while (s1[start])
	{
		if (!should_be_trimmed(s1[start], set))
		{
			trim_str_end = start;
		}
		start++;
	}
	return (trim_str_end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*ptr;
	size_t	trim_str_start;
	size_t	trim_str_end;

	if (!s1 || !set)
		return (NULL);
	if (!*s1)
	{
		ptr = malloc(1);
		if (!ptr)
			return (NULL);
		*ptr = '\0';
		return (ptr);
	}
	trim_str_start = get_start(s1, set);
	trim_str_end = get_end(s1, set, trim_str_start);
	len = trim_str_end + 1 - trim_str_start;
	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, &s1[trim_str_start], len);
	ptr[len] = '\0';
	return (ptr);
}
