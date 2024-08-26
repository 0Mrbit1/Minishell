#include "../../include/libft.h"

 pid_t output_redirection_append_mode(char *file_path , char *cmd_path  , char **argv , char **env)
 {
    int output_file_fd ; 

    output_file_fd = open(file_path , O_WRONLY | O_APPEND , 0644 );
    if (output_file_fd < 0)
    {
        perror("There was an error openning the input file");
        exit(1);
    }
    dup_fds(output_file_fd , STDOUT_FILENO ) ; 
    return execute_command(cmd_path ,argv , env) ;
 }