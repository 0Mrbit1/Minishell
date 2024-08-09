#include "libft.h"
#include <stdio.h>

typedef enum {
    HERE_DOC, //0 << 
	INPUT_REDIRECTION, //1 < 
	OUTPUT_REDIRECTION_APPEND_MODE, //2 >> 
    OUTPUT_REDIRECTION, //3 > 
	PIPES, //4 | 
	WORD //5 word
} TokenType;

typedef struct tokens
{
    const char *value;

    TokenType token_type; 
    
    struct tokens *next;

} token ;


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

token* tokenizer(char *prompt)
{
	typedef char (*redir_func_ptr)(char*);
	int i;
	int j;
	char **split_prompt;
    token* node;
    token* first_node;

	redir_func_ptr redirection_functions[] = {
        is_HERE_DOC,
		is_INPUT_REDIRECTION,
		is_OUTPUT_REDIRECTION_APPEND_MODE,
        is_OUTPUT_REDIRECTION,
		is_PIPES,
		is_WORD
	};
    i = 0;
	j = 0;
	
    split_prompt = ft_split(prompt, " \t");

    while (j < 6) 
    {
        if (redirection_functions[j](split_prompt[i]))
        {
            first_node = malloc(sizeof(token));
            first_node -> value = split_prompt[i] ;
            first_node -> token_type =  j;
            first_node -> next = NULL;
            break;
		}
		j++;
	}
    i++;
    j = 0;
    node = first_node ; 
	while (split_prompt[i])
    {
		while (j < 6) 
        {
			if (redirection_functions[j](split_prompt[i]))
            {
				node -> next = malloc(sizeof(token));
                node = node -> next;
                node -> value = split_prompt[i] ;
                node -> token_type =  j;
                node -> next = NULL ;
                if (!i)
                    first_node = node;
                break;
			}
			j++;
		}
        j = 0 ; 
		i++;
	}

	return first_node;
}


int main(int argc  , char **argv )
{
    token *node; 

    node = tokenizer(argv[1]) ;
    
    while(node)
    {
        printf("value %s\n" , node->value);
         printf("type %u\n" , node->token_type);
         printf("________________________________\n");
        node = node-> next ; 
    }

}