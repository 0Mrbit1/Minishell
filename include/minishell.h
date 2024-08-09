#include "libft.h"


typedef enum token_types
{
    INPUT_REDIRECTION,
    OUTPUT_REDIRECTION,
    OUTPUT_REDIRECTION_APPEND_MODE,
    HERE_DOC,
    PIPES,
    WORD
}type;

typedef struct tokens
{
    const char *value ;

    type    token_type ; 

} token ;

