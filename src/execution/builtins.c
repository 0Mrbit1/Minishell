#include "../../include/minishell.h"


int ft_strlen_delimiter(char *str , char delimiter)
{
    int i ; 

    i = 0 ;
    while (str[i]  && (str[i] != delimiter)   )
    {
        i++;
    }
    return i ; 

}
int search_key(char **env , char *to_search)
{
    int i ;
 
    i = 0 ;
    while (env[i])
    { 
        if (   !    ft_strncmp( env[i] , to_search  , ft_strlen_delimiter(env[i] , '=')  )            )  
        {
            return i ; 
        }
        i++;
    }
    return -1; 
}
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

char ft_cd(char* path , char **env)
{
    char *current_path; 
    struct stat fstats;
    int path_len ;
    char *home_path ; 
  

    if (!path)
    {
        home_path = env[   search_key(env , "HOME")   ] ;
      

        while(*home_path != '=')
            home_path++;
        chdir(++home_path); 
        return 1 ; 

    }

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