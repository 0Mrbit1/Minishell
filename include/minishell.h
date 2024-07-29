#include "libft.h"


typedef enum token_types
{
    COMMAND,
    COMMAND_FLAG,
    WORD_NO_INTERPRET,
    WORD_INTERPRET,
    INPUT_REDIRECTION,
    OUTPUT_REDIRECTION,
    HERE_DOC,
    HERE_DOC_DELIMITER,
    OUTPUT_REDIRECTION_APPEND_MODE,
    PIPES,
    ENV_VARIABLE,
    BUILTINS 
} type ;

typedef struct tokens
{

    const char *value ;

    type  token_type ; 

} token ;

