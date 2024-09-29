#include "mini_shell.h"

void output_redirection(char *file_path)
{
    int output_file_fd ; 

    output_file_fd = open(file_path , O_WRONLY  , 0644 );
    if (output_file_fd < 0)
         output_error_exit("There was an error openning the output file" , 1);
    dup_fds(output_file_fd , STDOUT_FILENO ) ; 
}