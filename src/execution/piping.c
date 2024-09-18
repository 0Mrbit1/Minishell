#include "../../include/minishell.h"

    
pid_t first_child_processe(char *cmd_path , char **argv , char **env, int **pipefd , int j )
{
    pid_t pid;
    int i ;

    i = 0;

    pid = fork();
    
    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (!pid)
    {
        dup2(pipefd[j][1] , STDOUT_FILENO);
        
        while (i < j)
        {
            close(pipefd[i][0]);
            close(pipefd[i][1]);
            i++;
        }
        execute_command(cmd_path , argv ,env); 
    }
    return pid;
}

pid_t middle_child_processes(char *cmd_path , char **argv ,  int **pipefd , char **env , int j )
{
    pid_t pid;
    int i ;

    i = 0 ;

    pid = fork(); 

    if (pid < 0)
    {
        perror("fork");
         exit(EXIT_FAILURE);
    }
    if (!pid)
    {
        dup_fds(pipefd[j][1] , STDOUT_FILENO);
        dup_fds(pipefd[j-1][0] , STDIN_FILENO);

        while (i < j)
    {
        close(pipefd[i][0]);
        close(pipefd[i][1]);
        i++;
    }
        execute_command(cmd_path , argv , env);
    }
    return pid;
}

pid_t ending_child_processe(char *cmd_path , char **argv , int **pipefd , char **env , int j )
{
    pid_t pid;
    int i ;

    i = 0 ;

    pid = fork(); 
    
    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (!pid)
    {
        dup_fds(pipefd[j-1][0] ,   STDIN_FILENO );

           while (i < j)
    {
        close(pipefd[i][0]);
        close(pipefd[i][1]);
        i++;
    }
        execute_command(cmd_path , argv , env);
    }
    return pid;
}

void    is_exit_with_signal(int *status)
{
    if (WIFEXITED(*status))
        *status = WEXITSTATUS(*status);
    else if (WIFSIGNALED(*status))
        *status = WTERMSIG(*status) + 128;
} 

int pipex(int argc , char **argv , char **env)
{
    int i;
    int j;
    char *cmd_path;
    int **fds; 
    char *av[2] ; 
    int status ; 
    int final_pid ;
    int pid  ; 
    int  final_status ;

    fds = malloc(sizeof(int*)  *  ( argc - 1 ) );
    j = 0 ; 
    while( j < argc -1 )
    {
        fds[j] = malloc(sizeof(int)*2);
        j++;
    }
    i = 1;
    j = 0;
    if (pipe(fds[j]) < 0)
        output_error_exit("There was an error creating the pipe" , EXIT_FAILURE);
    cmd_path = is_command(argv[i] , env);
    if (!cmd_path)
        cmd_path = argv[i];

    av[0] = argv[i]; 
    av[1] = NULL ;  
    
    first_child_processe(cmd_path , av , env, fds , j);
    i++;
    j++;
    while (i < argc - 1 ) 
    {
        cmd_path = is_command(argv[i], env);
        if (!cmd_path)
            cmd_path = argv[i];
        if ( pipe ( fds[j] )  < 0   )
            output_error_exit("There was an error creating the pipe" , EXIT_FAILURE);
        av[0] = argv[i]; 
        av[1] = NULL ;  
        middle_child_processes(cmd_path , av ,  fds , env , j  );
        j++ ;
        i++;
    }
    cmd_path = is_command(argv[i], env);    
    if (!cmd_path)
        cmd_path = argv[i];
    
    if ( pipe(fds[j]) < 0 )
        output_error_exit("There was an error creating the pipe" , EXIT_FAILURE);
    
    av[0] = argv[i];
    av[1] =  NULL;
    final_pid = ending_child_processe( cmd_path ,  av ,  fds ,  env , j);
    i = 0 ; 
    while (i < j)
    {

        close(fds[i][0]);
        close(fds[i][1]);
        i++;
    }

    while ((pid = wait(&status)) != -1) {
        
        if (pid == final_pid) {
            final_status = status ; 
           is_exit_with_signal(&final_status) ; 
        }
    }

    printf("%d" , final_status) ; 
    return 0 ; 
       
}

int main(int argc , char **argv , char **env)
{
    if (argc < 2 )
    {
        perror("Please inpu some arg , it should atleast two commands ") ; 
        return 1 ; 
    }

    pipex(argc , argv , env) ; 

}