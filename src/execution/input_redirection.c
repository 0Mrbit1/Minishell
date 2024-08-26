#include "../../include/libft.h"

pid_t  input_redirection (char *file_path , char *cmd_path , char **argv , char **env)
{
    int input_file_fd ; 

    input_file_fd = open(file_path , O_RDONLY , 0644 );
    if (input_file_fd < 0)
    {
        perror("There was an error openning the input file");
        exit(1);
    }
    dup_fds(input_file_fd , STDIN_FILENO ) ; 
    return execute_command(cmd_path ,argv , env) ; 
}