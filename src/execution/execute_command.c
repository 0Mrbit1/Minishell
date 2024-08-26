#include "../../include/libft.h"

pid_t execute_command(char *command_path , char **argv , char **env)
{
    pid_t pid ; 

    pid = fork() ; 
    
    if (!pid)
    {
        if ( execve(command_path , argv , env) < 0 ) 
        {
            perror("There was an error executing the command ") ; 
            exit (1);
        }
    }
    return pid;
}