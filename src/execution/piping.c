#include "../../include/libft.h"

char	*is_command(char *cmd, char **envp);
pid_t first_child_processe(char *cmd_path , int *pipefd , char **env )
{
    pid_t pid;

    pid = fork(); 

    char *arg1 = NULL;
    char *arg2 = NULL;
    char *args[] = {cmd_path, arg1, arg2, NULL};

    if (!pid)
    {
        close(pipefd[0]);
        if (dup2(pipefd[1] ,   STDOUT_FILENO ) < 0 )
        {   
            perror("There was an error dupping the first child process");
            exit(EXIT_FAILURE) ;
        }
        if(execve(cmd_path , args , env) < 0 )
        {
            perror("There was an error executing the first child process");
            exit(EXIT_FAILURE) ;
        }
    }
    return pid;
}


pid_t middle_child_processes(char *cmd_path , int *pipefd , char **env )
{
    pid_t pid;

    char *arg1 =  NULL;
    char *arg2 = NULL;

     char *args[] = {cmd_path, arg1, arg2, NULL};

    pid = fork(); 

    if (!pid)
    {
        if (dup2(pipefd[1] ,   STDOUT_FILENO ) < 0 )
        {
            perror("There was an error dupping a mild child process");
            exit(EXIT_FAILURE) ;
        }
        if ( dup2(pipefd[0] ,   STDIN_FILENO )< 0 )
        {
            perror("There was an error dupping a mild child process");
            exit(EXIT_FAILURE) ;
        }
        if(execve(cmd_path , args , env) < 0 )
        {
            perror("There was an error executing a mild child process");
            exit(EXIT_FAILURE) ;
        }
    }
    return pid;
}

pid_t ending_child_processe(char *cmd_path , int *pipefd , char **env)
{
    pid_t pid;

    pid = fork(); 

    char *arg1 = NULL;
    char *arg2 = NULL;

     char *args[] = {cmd_path, arg1, arg2, NULL};

    if (!pid)
    {
        close(pipefd[1]);
        if ( dup2(pipefd[0] ,   STDIN_FILENO )< 0 )
        {
            perror("There was an error dupping the ending child process");
            exit(EXIT_FAILURE) ;
        }
        if(execve(cmd_path , args , env) < 0 )
        {
            perror("There was an error executing the ending child process");
            exit(EXIT_FAILURE) ;
        }
    }
    return pid;
}

int main(int argc , char **argv , char **env)
{
    int i ;
    int pipefd[2];
    char *cmd_path;

    i = 1 ; 
    if (argc < 2)
    {
        perror("please entre some arguments") ; 
        exit(EXIT_FAILURE) ; 
    }
    if (pipe(pipefd) < 0)
    {
        perror("There was an error creating the pipe");
        exit(EXIT_FAILURE);
    }
    cmd_path = is_command(argv[i], env);
    if (!cmd_path)
        cmd_path = argv[i] ; 
    first_child_processe(cmd_path , pipefd , env) ; 
    i++;
    while (i < argc  - 1 ) 
    {
        cmd_path = is_command(argv[i], env);
        if (!cmd_path)
            cmd_path = argv[i] ; 
        middle_child_processes(cmd_path , pipefd , env );
        i++;
    }
    cmd_path = is_command(argv[i], env);
    if (!cmd_path)
        cmd_path = argv[i] ; 

    ending_child_processe(cmd_path , pipefd , env) ; 
    close(pipefd[0]);
    close(pipefd[1]);
    while (wait(NULL) > 0);
        
}