#include "../../include/minishell.h"

    
pid_t first_child_processe(t_command *prompt  ,  char *cmd_path , char **argv , char **env, int **pipefd , int j )
{
    pid_t pid;
    int i ;
    int fd ;

    if (!strcmp(prompt->command , "cd"))
    {
       ft_cd((prompt->args)[1] , env);
        return 0 ; 
    }

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
        close (pipefd[j][0]);
        if (prompt->input_redirect)
        {
            fd = open(prompt->input_redirect , O_RDONLY) ; 
            dup2(fd , STDIN_FILENO );  
        }
        if (prompt->output_redirect)
        {
            fd = open(prompt->output_redirect , O_WRONLY| O_CREAT) ; 
            dup2(fd , STDOUT_FILENO );  
        }
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

pid_t middle_child_processes(t_command *prompt  , char *cmd_path , char **argv ,  int **pipefd , char **env , int j )
{
    pid_t pid;
    int i ;
    int fd ; 

    i = 0 ;

      if (!strcmp(prompt->command , "cd"))
    {
        ft_cd((prompt->args)[1]  , env); 
        return 0 ; 
    }

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

        if (prompt->input_redirect)
        {
            fd = open(prompt->input_redirect , O_RDONLY) ; 
            dup2(fd , STDIN_FILENO );  
        }

        if (prompt->output_redirect)
        {
            fd = open(prompt->output_redirect , O_WRONLY| O_CREAT) ; 
            dup2(fd , STDOUT_FILENO );  
        }

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

pid_t ending_child_processe(t_command *prompt , char *cmd_path , char **argv , int **pipefd , char **env , int j )
{
    pid_t pid;
    int i ;
    int fd ;

      if (!strcmp(prompt->command , "cd"))
    {
            ft_cd((prompt->args)[1], env);
        return 0 ; 
    } 

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
        if (prompt->input_redirect)
        {
            fd = open(prompt->input_redirect , O_RDONLY) ; 
            dup2(fd , STDIN_FILENO );  
        }

        if (prompt->output_redirect)
        {
            fd = open(prompt->output_redirect , O_WRONLY | O_CREAT) ;
            dup2(fd , STDOUT_FILENO );  
        }
        
        while (i < j )
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

int pipex(t_command *prompt , char **env)
{
    int  j;
    char *cmd_path;
    int  **fds;
    int  status;
    int  final_pid;
    int  pid;
    int  final_status;
    int lst_size;
    int fd ;

    lst_size = ft_lstsize(prompt);
    fds = malloc(sizeof(int*)*( lst_size ));
    j = 0;
    while( j < lst_size )
    {
        fds[j] = malloc(sizeof(int)*2);
        j++;
    }
    j = 0;
    if (lst_size == 1)
    {
        cmd_path = is_command(prompt->command , env);
        if (!cmd_path)
            cmd_path = prompt->command;

        if (!strcmp(prompt->command , "cd"))
        {
            ft_cd((prompt->args)[1], env) ; 
            return 0 ; 
        }
        pid = fork() ; 

        if (!pid)
        {

        if (prompt->input_redirect)
        {
            fd = open(prompt->input_redirect , O_RDONLY) ; 
            dup2(fd , STDIN_FILENO );  
        }

        if (prompt->output_redirect)
        {
            fd = open(prompt->output_redirect , O_WRONLY | O_CREAT) ; 
            dup2(fd , STDOUT_FILENO );  
        }
        if (execve(cmd_path , prompt->args , env) < 0 ) 
                output_error_exit("command" , 127);
        }
        wait(NULL);
        return 0 ; 
    }
        if (pipe(fds[j]) < 0)
            output_error_exit("pipe" , EXIT_FAILURE);
        cmd_path = is_command(prompt->command , env);
        if (!cmd_path)
            cmd_path = prompt->command;

        first_child_processe(prompt , cmd_path , prompt->args , env, fds , j);
        j++;
        prompt = prompt -> next ;
     
    while (j < lst_size - 1  ) 
    {
        cmd_path = is_command(prompt->command, env);
        if (!cmd_path)
            cmd_path = prompt->command;
        if ( pipe ( fds[j] )  < 0   )
            output_error_exit("pipe" , EXIT_FAILURE);  
        middle_child_processes(prompt , cmd_path , prompt->args ,  fds , env , j  );
        j++ ;
       prompt = prompt -> next ; 
    }
    cmd_path = is_command(prompt->command, env); 
    if (!cmd_path)
    {
        cmd_path = prompt->command;
    }
    if ( pipe(fds[j]) < 0 )
        output_error_exit("pipe" , EXIT_FAILURE);
    
    final_pid = ending_child_processe(prompt, cmd_path ,  prompt->args ,  fds ,  env , j);
    j = 0 ; 
    while (j < lst_size  )
        {
            close(fds[j][0]);
            close(fds[j][1]);
            j++;
        }
    while ((pid = wait(&status)) != -1) {
        if (pid == final_pid) {
            final_status = status ; 
           is_exit_with_signal(&final_status) ; 
        }
    }
    return 0 ;
}

int main(int argc , char **argv , char **env)
{

    char *input = NULL;
    token *tokens = NULL;
    t_command *cmd_list = NULL;
    
    (void)argc ;
    (void)argv;

    while (1337) 
    {
        input=readline("babyshell(*-*)> ");
        
        /******/    
        
        tokens = tokenizer(input);   
        cmd_list = parse_command(tokens); 

        pipex(cmd_list , env) ; 
        free(input);
        input = NULL;
     }
    return 0;


}