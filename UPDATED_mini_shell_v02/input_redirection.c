#include "mini_shell.h"

void  input_redirection (char *file_path )
{
    int input_file_fd ; 

    input_file_fd = open(file_path , O_RDONLY , 0644 );
    if (input_file_fd < 0)
        output_error_exit("there was an error openning the input file" , 1);
    dup_fds(input_file_fd , STDIN_FILENO ) ; 
}