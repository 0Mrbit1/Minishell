#include "../../include/minishell.h"

void ft_echo(int line , char *str)
{
    if (line)
    {
        write(STDIN_FILENO , str ,  sizeof(char)*ft_strlen(str)); 
        write(STDIN_FILENO , "\n" , sizeof(char)); 
    }
    else
        write(STDIN_FILENO , str , sizeof(char)*ft_strlen(str) );
}

void ft_env(char **envp)
{
    int i ;
    i = 0 ;

    while(envp[i])
    {
        printf("%s" , envp[i]);
        i++;
    }
}

char ft_cd(char* path)
{
    char *current_path; 
    struct stat fstats;
    int path_len ;

    path_len = ft_strlen (path)  + 1 ;
    if (stat(path, &fstats) < 0)
    {
        perror("there was an error getting the file stats");
        return -1; 
    }
    if (!S_ISDIR(fstats.st_mode))
    {
        perror("Not a directory");
        return -1;
    }
    if (access(path, X_OK))
    {
        perror("cannot access the directory");
        return -1;
    }
    chdir(path); 
    current_path = malloc(sizeof(char)  * path_len  ) ;
    getcwd(current_path , path_len); 
    printf("%s" , current_path ); 
    free(current_path);
    return 0;
}

char *ft_pwd()
{

    char    *buffer;
    int     size;
    char *current_dir ; 

    size = 19 ;
    buffer = malloc(sizeof(char)*size) ;

   while (!getcwd (buffer ,  size ) )  
   {
        free(buffer);
        size *= 2; 
        buffer = malloc(sizeof(char)*size) ; 
    }
    current_dir = ft_strdup(buffer) ;
    free(buffer);
    return current_dir ; 
}