#include "../../include/minishell.h"
// tokenize and parse the input

 typedef struct s_command
{
    char *command;            
    char **args;              
    char *input_redirect;     
    char *output_redirect;     
    int append_mode;           
    struct s_command *next;    
} t_command;

void execute_prompt(t_command *prompt , char **env ) 
{

    int fd ; 
    int pipefd[2]; 
    int j = 0 ; 
    int pid ; 
    char *command_path ; 
    
    while (prompt)
    {
        if (prompt->input_redirect)
        {
            fd = open(prompt->input_redirect  , O_RDONLY ) ; 
            dup_fds( fd , STDIN_FILENO  ) ; 
        }
        if (prompt->next)
        {
            pipe(pipefd);
            if ( j == 0 )
            {
                dup_fds(  pipefd[1]      , STDOUT_FILENO  ) ;
                close(pipefd[0]) ; 
            }
        }
        if (prompt->output_redirect)
        {
            fd = open(prompt->output_redirect  , O_WRONLY ) ; 
            dup_fds( fd , STDOUT_FILENO ) ;
        }
        pid = fork() ; 
        if (!pid)
        {
            command_path = is_command(prompt->command, env) ; 
            execute_command(command_path , prompt -> args , env) ; 
        }

    }







}
int main()
{
    char *input = NULL;
    token *tokens = NULL;
    t_command *cmd_list = NULL;

    while (1337) 
    {
        input=readline("minishell(*-*)> ");  
        tokens = tokenizer(input);   
        cmd_list = parse_command(tokens);
        free(input);
        input = NULL;
     }
    return 0;
}