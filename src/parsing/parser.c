#include "../../include/minishell.h"


commands_data  parser(char *prompt)
{
    int i ;
    token *tokens;
    commands_data *first_node; 

    first_node = malloc(sizeof(commands_data)) ; 

    tokens = tokenizer(prompt) ;
    i = 0 ; 
    while (tokens)
    {
   

    }
}



















