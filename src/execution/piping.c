#include "../../include/minishell.h"

void execute_command(char *cmd_path, char **argv, char **env);
void dup_fds(int old_fd, int new_fd);
void output_error_exit(const char *msg, int exit_code);
char *is_command(const char *cmd, char **env);

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

int pipex(int argc , char **argv , char **env)
{
    int i;
    int j;
    char *cmd_path;
    int **fds; 
    char *av[2] ; 

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
    ending_child_processe(cmd_path , av , fds , env , j );
    i = 0 ; 
    while (i < j)
    {
        close(fds[i][0]);
        close(fds[i][1]);
        i++;
    }
    while (wait(NULL) != -1);
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