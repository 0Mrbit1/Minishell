#include "../../include/minishell.h"

typedef enum {
    INPUT_REDIRECTION,
    OUTPUT_REDIRECTION,
    OUTPUT_REDIRECTION_APPEND_MODE,
    HERE_DOC,
    PIPES,
    WORD
} TokenType;

char is_INPUT_REDIRECTION(char *str) {
    if (*str == '<')
        return 1;
    return 0;
}

char is_OUTPUT_REDIRECTION(char *str) {
    if (*str ==  '>') 
        return 1;
    return 0;
}

char is_HERE_DOC(char *str) {
    if (ft_strncmp(str, "<<", 2) == 0)
        return 1;
    return 0;
}

char is_OUTPUT_REDIRECTION_APPEND_MODE(char *str) {
    if (ft_strncmp(str, ">>", 2) == 0)
        return 1;
    return 0;
}

char is_PIPES(char *str)
{   
	if (*str == '|')
        return 1;
    return 0;
}

char is_WORD(char *str)
{
	return 1; 
}

TokenType *tokenizer(char *prompt)
{
	typedef char (*redir_func_ptr)(char *);
	int i;
	int j;
	char **split_prompt;
	TokenType *tokens;
	int token_count;

	i = 0;
	j = 0;
	token_count = 0;

	redir_func_ptr redirection_functions[] = {
		is_INPUT_REDIRECTION,
		is_OUTPUT_REDIRECTION,
		is_OUTPUT_REDIRECTION_APPEND_MODE,
		is_HERE_DOC,
		is_PIPES,
		is_WORD
	};

	split_prompt = ft_split(prompt, " \t");

	// Allocate memory for the tokens array (assuming we have enough tokens)
	tokens = malloc(sizeof(TokenType) * ft_split_count(split_prompt));

	while (split_prompt[i]) {
		j = 0;
		while (j < sizeof(redirection_functions) / sizeof(redirection_functions[0])) {
			if (redirection_functions[j](split_prompt[i])) {
				tokens[token_count++] = (TokenType)j;
				break; // Stop checking other functions once a match is found
			}
			j++;
		}
		i++;
	}

	// Free the split_prompt array
	ft_free_split(split_prompt);

	return tokens;
}
