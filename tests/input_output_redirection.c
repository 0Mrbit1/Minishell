#include "libft.h"

pid_t  input_redirection (int input_file_fd , char *cmd_path , char ** args , char **env)
{
    pid_t pid;

    char **argv ; 

    argv = malloc(sizeof(char*)) ; 

    argv[0] = NULL ; 

     if (input_file_fd < 0)
    {
        perror("There was an error openning the input file");
        exit(1);
    }


    
    pid = fork();
    if (pid < 0)
    {
        perror("There was an error creating a child process");
        exit(1);
    }


    if (!pid)
    { 
        if (dup2(  input_file_fd   ,    STDIN_FILENO   ) < 0 )
        {
            perror("There was an error in output redirection");
            exit(1);
        }
        if (execve(cmd_path , argv , env)  < 0)  
        {   
            perror("There was an error executing the command after output redirection");
            exit(1) ; 
        }
    }

    return pid ; 
}

pid_t output_redirection(int output_file_fd , char *cmd_path , char **args , char **env)
{

    pid_t pid;

    char **argv ; 

    argv = malloc(sizeof(char*)) ; 

    argv[0] = NULL ;

    if (output_file_fd < 0)
    {
        perror("There was an error openning the output file");
        exit(1);
    }

    pid = fork();
    if (pid < 0)
    {
        perror("There was an error creating a child process");
        exit(1);
    }

    if (!pid)
    {
        
        if (dup2(  output_file_fd   ,    STDOUT_FILENO   ) < 0 )
        {

            perror("There was an error in output redirection");

            exit(1);

        }
        
        if (execve(cmd_path , argv , env)  < 0)  
        {
            
            perror("There was an error executing the command after output redirection");

            exit(1) ; 

        }

    }
    return pid;

}

int main(int argc , char **argv , char **env)
{
    int fd ;

    if (argc < 2 )
    {
        perror("Please give some argument");
        exit(1);
    }

    fd = open(argv[1] , O_RDWR );
 
    output_redirection(fd , argv[2], argv , env);
}