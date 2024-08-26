#include "../../include/libft.h"

void input_redirection_herdoc(char *delimiter  , char **env , char **argv)
 {

    int fd ;
    int delimiter_len;
    char *buffer;
    int bytes_read; 

    fd = open("herdoc" , O_RDWR | O_CREAT , 0644 );
    delimiter_len = ft_strlen(delimiter);
    buffer = malloc(sizeof(char)*delimiter_len  + 1 ) ; 
     while(1)
    {
        bytes_read = read (STDIN_FILENO , buffer , delimiter_len) ;
        buffer[bytes_read] = '\0'; 
        if (!ft_strncmp(buffer, delimiter, ft_strlen(buffer) + delimiter_len )) 
        {
            break;
        }
        write(fd , buffer , ft_strlen(buffer)) ;
    }
    free(buffer) ; 
    fd = open("herdoc" , O_RDWR , 0644 );
    if ( dup2(fd , STDIN_FILENO) < 0 ) 
    {
        perror("There was an error redirecting stdin") ; 
        exit(1);
    }
    pid_t pid ; 
    pid = fork() ; 

    if (!pid)
    {
        if ( execve("/usr/bin/cat" , argv , env) <  0 ) 
        {
            perror("There was an error executing the command ") ; 
            exit (1);
        }
    }
    unlink("herdoc");
 }

