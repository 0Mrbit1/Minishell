/*#include "minishell.h"

#ifndef TOKENIZ_H
# define TOKENIZ_H


typedef char (*redir_func_ptr)(char*);

typedef enum {
    HERE_DOC, 
	INPUT_REDIRECTION, 
	OUTPUT_REDIRECTION_APPEND_MODE,
    OUTPUT_REDIRECTION, 
	PIPES, 
	WORD 
} TokenType;

typedef struct tokens
{
    char *value;

    TokenType token_type; 
    
    struct tokens *next;

} token ;


char is_INPUT_REDIRECTION(char *str) ;

char is_OUTPUT_REDIRECTION(char *str) ;


char is_HERE_DOC(char *str) ;


char is_OUTPUT_REDIRECTION_APPEND_MODE(char *str) ;

char is_PIPES(char *str) ;


char is_WORD(char *str);
token	*tokenizer(char *prompt)  ;
#endif*/
