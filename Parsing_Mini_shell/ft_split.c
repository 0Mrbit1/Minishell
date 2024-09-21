#include "mini_shell.h"
 
static char	**free_array(char **ptr, int count)
{
	while (count--)
	{
		free(ptr[count]);
	}
	free(ptr);
	return (NULL);
}

int	count_words(char const *str, char c)
{
	int	i;
	int	f;
	int	counter;

	i = 0;
	f = 1;
	counter = 0;
	while (str[i])
	{
		if (str[i] != '\0' && str[i] != c && str[i] != '\t')
		{
			if (f == 1)
			{
				counter++;
				f = 0;
			}
		}
		else
			f = 1;
		i++;
	}
	return (counter);
}

static char	*mword(char const *str, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *str, char c)
{
	char	**tab;
	int		i;

	if (!str)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	tab[count_words(str, c)] = NULL;
	while (*str)
	{
		while (*str && (*str == c))
			str++;
		if (*str && *str != c)
		{
			tab[i] = mword(str, c);
			if (!tab[i])
				return (free_array(tab, i));
			i++;
			while (*str && *str != c)
				str++;
		}
	}
	return (tab);
}

