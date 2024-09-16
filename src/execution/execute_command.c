#include "../../include/minishell.h"

void execute_command(char *command_path , char **argv , char **env)
{
   
    if (execve(command_path , argv , env) < 0 ) 
            output_error_exit("there was en error executing the command" , 127);
}