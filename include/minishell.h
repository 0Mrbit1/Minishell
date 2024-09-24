

#ifndef MINISHELL_H
# define MINISHELL_H

 typedef struct s_command
{
    char *command;            
    char **args;              
    char *input_redirect;     
    char *output_redirect;     
    int append_mode;           
    struct s_command *next;    
} t_command;

#include "libft.h"
#include "parsing.h"
#include "execution.h"
//#include "tokenizer.h"



#endif