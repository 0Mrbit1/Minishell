#include "libft.h"


pid_t  input_redirection (int input_file_fd , char *cmd)
{
    pid_t pid;

    
    pid = fork();
    if (pid < 0)
    {
        perror("There was an error creating a child process");
        exit(1);
    }


    if (!pid)
    { 
        if (dup2(  input_file_fd   ,    STDOUT_FILENO   ) < 0 )
        {
            perror("There was an error in output redirection");
            exit(1);
        }
        if (execve(cmd_path , args , env)  < 0)  
        {   
            perror("There was an error executing the command after output redirection");
            exit(1) ; 
        }
    }
}

pid_t output_redirection(int output_file_fd , char *cmd)
{

    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
        perror("There was an error creating a child process");
        exit(1);
    }

    if (!pid)
    {
        
        if (dup2(  output_file_fd   ,    STDIN_FILENO   ) < 0 )
        {

            perror("There was an error in output redirection");

            exit(1);

        }
        
        if (execve(cmd_path , args , env)  < 0)  
        {
            
            perror("There was an error executing the command after output redirection");

            exit(1) ; 

        }

    }


}