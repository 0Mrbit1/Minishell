#include "mini_shell.h"

void dup_fds(int old_fd , int new_fd)
{
    if ( dup2(old_fd , new_fd) < 0 ) 
        output_error_exit("there was an error duping the files fds" , 1);
}