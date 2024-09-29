#include "mini_shell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = strlen(s1);
	s2_len = strlen(s2);
	str = (char *)malloc(s1_len + s2_len + 1);
	if (!str)
		return (NULL);
	memcpy(str, s1, s1_len);
    memcpy(&str[s1_len], s2, s2_len + 1);
	return (str);
}