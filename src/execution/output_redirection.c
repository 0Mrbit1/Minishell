#include "../../include/minishell.h"


pid_t output_redirection(char *file_path , char *cmd_path , char **argv , char **env)
{
    int output_file_fd ; 

    output_file_fd = open(file_path , O_WRONLY  , 0644 );
    if (output_file_fd < 0)
         output_error_exit("There was an error openning the output file" , 1);
    dup_fds(output_file_fd , STDOUT_FILENO ) ; 
    return execute_command(cmd_path , argv , env) ;
}