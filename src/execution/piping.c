#include "../../include/libft.h"

pid_t first_child_processe(char *cmd_path , int *pipefd , char **env )
{
    pid_t pid;

    pid = fork(); 

    if (!pid)
    {
        close(pipefd[0]);
        dup2(pipefd[1] ,   STDOUT_FILENO );
        execute_command(cmd_path , argv ,env);

    }
    return pid;
}

pid_t middle_child_processes(char *cmd_path , char **argv ,  int *pipefd , char **env )
{
    pid_t pid;

    pid = fork(); 

    if (!pid)
    {
        dup_fds(pipefd[1] , STDOUT_FILENO);
        dup_fds(pipefd[0] , STDIN_FILENO);
        execute_command(cmd_path , argv , env);
    }
    return pid;
}

pid_t ending_child_processe(char *cmd_path , int *pipefd , char **env)
{
    pid_t pid;

    pid = fork(); 
    if (!pid)
    {
        close(pipefd[1]);
        dup_fds(pipefd[0] ,   STDIN_FILENO );
        execute_command(cmd_path , argv , env);
    }
    return pid;
}

int pipex(int argc , char **argv , char **env)
{
    int i ;
    int pipefd[2];
    char *cmd_path;

    i = 1;
    if (pipe(pipefd) < 0)
        output_error_exit("There was an error creating the pipe" , 1);
    cmd_path = is_command(argv[i] , env);
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