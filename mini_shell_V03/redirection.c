#include "mini_shell.h"

 
int is_HERE_DOC(char *token)
{
    if (!token)
        return 0;
    return (strcmp(token, "<<") == 0);
}

 
int is_INPUT_REDIRECTION(char *token)
{
    if (!token)
        return 0;
    return (strcmp(token, "<") == 0);
}

 
int is_OUTPUT_REDIRECTION_APPEND_MODE(char *token)
{
    if (!token)
        return 0;
    return (strcmp(token, ">>") == 0);
}
 
int is_OUTPUT_REDIRECTION(char *token)
{
    if (!token)
        return 0;
    return (strcmp(token, ">") == 0);
}

 
int is_PIPES(char *token)
{
    if (!token)
        return 0;
    return (strcmp(token, "|") == 0);
}
 
int is_WORD(char *token)
{
    //   is valid and not a special symbol
    if (token && !is_HERE_DOC(token) && !is_INPUT_REDIRECTION(token) && !is_OUTPUT_REDIRECTION_APPEND_MODE(token) && !is_OUTPUT_REDIRECTION(token) &&!is_PIPES(token))
    {
        return 1;  // it is a word 
    }
    return 0;      // it is a special symbol
}
