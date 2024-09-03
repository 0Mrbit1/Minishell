#include "libft.h"

void ft_echo(int line , char *str)
{
    //echo by default output a line

    if (line)
    {
        write(STDIN_FILENO , str ,  sizeof(char)*ft_strlen(str)); 
        write(STDIN_FILENO , "\n" , sizeof(char)); 
    }
    else
        write(STDIN_FILENO , str , sizeof(char)*ft_strlen(str) );
}

void ft_env(char **envp  )
{
    int i ;
    i = 0 ;

    while(envp[i])
    {
        printf("%s" , envp[i]);
        i++;
    }
}

void ft_cd()
{

    
}

