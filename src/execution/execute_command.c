#include "../../include/minishell.h"

pid_t execute_command(char *command_path , char **argv , char **env)
{
    pid_t pid ; 

    pid = fork() ; 
    
    if (!pid)
    {
        if (execve(command_path , argv , env) < 0 ) 
            output_error_exit("there was en error executing the command" , 1);
    }
    return pid;
}