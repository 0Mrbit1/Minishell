



char is_INPUT_REDIRECTION(char *str) {
    if (!ft_strncmp(str, "<", ft_strlen(str) + 1 ))
        return 1;
    return 0;
}

char is_OUTPUT_REDIRECTION(char *str) {
    if (!ft_strncmp(str, ">", ft_strlen(str) + 1 ) ) 
        return 1;
    return 0;
}

char is_HERE_DOC(char *str) {
    if (!ft_strncmp(str, "<<", ft_strlen(str) + 2))
    {
        return 1;
    }
    return 0;
}

char is_OUTPUT_REDIRECTION_APPEND_MODE(char *str) {
    if (!ft_strncmp(str, ">>", ft_strlen(str) + 2 ))
        return 1;
    return 0;
}

char is_PIPES(char *str)
{   
	if (!ft_strncmp(str, "|", ft_strlen(str) + 1 ))
        return 1;
    return 0;
}

char is_WORD(char *str)
{
	return 1; 
}