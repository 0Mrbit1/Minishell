#include "../../include/minishell.h"

static char *with_line (char *last_line  , char *line  , short *line_found )
{
    char *final_line ; 
    
    if (!last_line)
        final_line = line  ; 
    else
    {
        final_line = ft_strjoin(last_line , line );
        free(line);
        free(last_line);
    }
    *line_found = 1 ; 
    return final_line; 
}

static char *without_line (char **buffer , char *last_line   , char *line)
{
    char *final_line ; 

    free(*buffer);
    *buffer = NULL ;
    if (!last_line)
        final_line = line ;
    else
    {
        final_line = ft_strjoin(last_line , line );
        free(line);
        free(last_line);
    }
    return final_line;
}

static char *build_line(char **buffer , int bytes_read , char *last_line , short *line_found )
{
    int i;
    char *line;

    i = 0;
    line = (char*)malloc((bytes_read + 1 )* sizeof(char) );
    if (!line)
        return NULL;
    while((*buffer)[i])
    {
        line[i] = (*buffer)[i] ;
        if ((*buffer)[i] == '\n')
        {
            ft_memmove(*buffer ,  &((*buffer)[i+1])    , bytes_read - i) ; 
            line[++i] = '\0';
            if ((*buffer)[i] == '\0')
            {
                free(*buffer);
                *buffer = NULL ;
            }
            return with_line (last_line  , line  , line_found ); 
        }
        i++;
    }
    line[i] = '\0';
    return without_line (buffer , last_line , line);
}

char *read_file(int fd , char *buffer  , ssize_t *bytes_read)
{
    char *clean;

    if (buffer)
    {
        *bytes_read = ft_strlen(buffer);
        return buffer;
    }
    buffer = (char*)malloc((BUFFER_SIZE +1) * sizeof(char)  );
    if (!buffer)
        return  NULL;
    *bytes_read = read( fd , buffer , BUFFER_SIZE ) ;
    buffer[*bytes_read] = '\0';
    clean = buffer ;
    buffer = ft_strdup(buffer) ;
    free(clean); 
    if (!*bytes_read)
    {
        free(buffer);
        buffer = NULL;
    }
    return buffer;
}

char *get_next_line(int fd)
{
   ssize_t bytes_read;
   static char *buffer;
   char *line;
   short line_found ; 
  
   line_found = 0;
   line = NULL;
   while (1)
   {
        buffer = read_file(fd , buffer  , &bytes_read); 
        if (buffer && !line_found)
        {
            line = build_line(&buffer , bytes_read , line , &line_found );
            if (line_found)
                return line ;
        } 
        else 
            return line ;
   }
}
