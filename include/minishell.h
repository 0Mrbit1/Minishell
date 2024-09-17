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


typedef struct command_attibutes
{
    char *here_doc_file;
	char *input_file;
	char *output_file;
    short append_mode; 
	short pipe_connected;
    char *command;
    
    struct tokens *command_attibutes;

} commands_data;


char is_INPUT_REDIRECTION(char *str) ;

char is_OUTPUT_REDIRECTION(char *str) ;


char is_HERE_DOC(char *str) ;


char is_OUTPUT_REDIRECTION_APPEND_MODE(char *str) ;

char is_PIPES(char *str) ;


char is_WORD(char *str);







