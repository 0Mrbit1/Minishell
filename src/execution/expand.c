#include "../../include/minishell.h"

int calculate_array_size(char **array)
{
    int i ;

    i = 0;

    while(array[i])
        i++;
    return i ;
}


char **expand_array(char **last_array)
{
int i;
char **new_array ; 
int array_size ; 

i = 0 ;
array_size = calculate_array_size(last_array) ; 
new_array = malloc(sizeof(char*)*( array_size + 2  )    ) ; 

while (last_array[i])
{
    new_array[i] = malloc(sizeof(char) *  ( ft_strlen(last_array[i]) + 1 )  ) ; 

    ft_memmove( new_array[i]   , last_array[i]  ,  ft_strlen( last_array[i] ) + 1  ) ; 
    i++ ; 
}
new_array[i] = NULL ; 
ft_free_split(last_array);
return new_array ; 


}



char  **ft_export(char **last_env , char *variable)
{

    char **bigger_env ;
    int i ;

    i = 0 ; 

    bigger_env = expand_array(last_env);
    while (bigger_env[i])
    {
        i++;
    }
    bigger_env[i++] = ft_strdup(variable) ;
    bigger_env[i] = NULL ;

    return bigger_env ;
}

int main(int argc , char **argv , char **env )
{

    int i ; 
    int array_size ; 
    char **new_env ; 
    char **added_data ; 

    i = 0 ; 
    array_size = calculate_array_size(env) ; 
    new_env = malloc(sizeof(char*) * (array_size + 1 )) ; 


    while(env[i])
    {
        new_env[i] = ft_strdup(env[i]) ;
        i++;
    }
    new_env[i] = NULL ; 

    added_data = ft_export(new_env , "tes=1337") ; 
    i = 0 ; 

    while(added_data[i])
    {
        printf("%s\n" , added_data[i]);
        i++;
    }
    return 0 ; 




}