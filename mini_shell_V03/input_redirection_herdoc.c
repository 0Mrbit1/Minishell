#include "mini_shell.h"

void redidrect_stdin_to_herdoc(char *delimiter )
{
    int heredoc_fd ;
    int delimiter_len;
    char *buffer;
    int bytes_read; 


    heredoc_fd = open(".heredoc" , O_RDWR | O_CREAT , 0644 );
    if (heredoc_fd < 0)
        output_error_exit("there was an error creating herdoc file" , 1);
    delimiter_len = strlen(delimiter);
    buffer = malloc(sizeof(char)*delimiter_len  + 1 ) ; 
    if (!buffer)
        output_error_exit("Not Enought memory" , 1);
    while(1)
    {
        bytes_read = read (STDIN_FILENO , buffer , delimiter_len) ;
        buffer[bytes_read] = '\0'; 
        if (!strncmp(buffer, delimiter, strlen(buffer) + delimiter_len )) 
            break;
        write(heredoc_fd , buffer , strlen(buffer)) ;
    }
    free(buffer);
}

void input_redirection_herdoc(char *delimiter )
 {
    int heredoc_fd ; 
    
    redidrect_stdin_to_herdoc(delimiter ); 
    heredoc_fd  = open(".herdoc" , O_RDWR , 0644 );
     if (heredoc_fd < 0)
        output_error_exit("there was an error openning herdoc file" , 1);
    dup_fds(heredoc_fd , STDIN_FILENO);
 }

