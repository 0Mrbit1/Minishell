#include "../../include/libft.h"



void output_error_exit(char *error_msg , int status)
{
    perror(error_msg);
    exit(status);
}