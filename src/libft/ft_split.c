/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharik <acharik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 06:49:49 by acharik           #+#    #+#             */
/*   Updated: 2024/08/06 09:54:19 by acharik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	is_delimiter(char c, char *delimiters)
{
	int	i;

	i = 0;
	while (delimiters[i])
	{
		if (c == delimiters[i])
			return (1);
		i++;
	}
	return (0);
}

int	skip_delimiters(const char *str, int *i, char *delimiters, int flag)
{
	if (flag)
	{
		while (str[*i + 1] && is_delimiter(str[*i], delimiters))
			(*i)++;
	}
	else
	{
		while (str[*i + 1] && !is_delimiter(str[*i], delimiters))
			// nor delimters
			(*i)++;
	}
	return (*i);
}

static int	words_count(const char *str, char *delimiters)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i])
	{
		if (!is_delimiter(str[i], delimiters))
		{
			skip_delimiters(str, &i, delimiters, 0);
			words++;
		}
		i++;
	}
	return (words);
}

static void	store_data(char **dest, const char *src, int str_size, char is_end)
{
	if (!is_end)
		str_size++;
	*dest = malloc(sizeof(char) * (str_size + 1));
	ft_memmove(*dest, src, str_size);
	(*dest)[str_size] = '\0';
}

char	**ft_split(const char *str, char *delimiters)
{
	int		i;
	int		j;
	int		str_size;
	int		start;
	char	**split;

	i = 0;
	j = 0;
	split = malloc(sizeof(char *) * (words_count(str, delimiters) + 1));
	start = skip_delimiters(str, &i, delimiters, 1);
	while (str[i])
	{
		if (is_delimiter(str[i], delimiters) || !str[i + 1])
		{
			str_size = i - start;
			store_data(&(split[j]), &(str[start]), str_size, str[i + 1]);
			j++;
			start = skip_delimiters(str, &i, delimiters, 1);
		}
		i++;
	}
	split[j] = NULL;
	return (split);
}
