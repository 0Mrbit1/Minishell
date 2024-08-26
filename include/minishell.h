#include "libft.h"

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


