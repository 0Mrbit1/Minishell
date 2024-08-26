#include "../../include/libft.h"

void dup_fds(int old_fd , int new_fd)
{
    if ( dup2(old_fd , new_fd) < 0 ) 
    {
        perror("There was an error redirecting stdin") ; 
        exit(1);
    }
}