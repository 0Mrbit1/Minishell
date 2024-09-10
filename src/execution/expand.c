#include "../../include/minishell.h"

int calculate_array_size(char **array)
{
    int i ;

    i = 0;
    while(array[i])
        i++;
    return i;
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
    new_array[i] = ft_strdup(last_array[i]);
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
    bigger_env[i] = ft_strdup(variable) ;
    i++;
    bigger_env[i] = NULL ;

    return bigger_env ;
}

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

char **ft_unset(char **env  , char *var)
{
    int i ;
    int j ;
    char **smaller_array ;
    int array_size ; 
    int key ; 

    key = search_key(env , var) ;

    i = 0 ;
    j = 0 ;
    array_size = calculate_array_size(env) ; 
    smaller_array  =  malloc( sizeof(char*)*(array_size) ); 
    while(env[i])
    {
        if (i != key )
        { 
            smaller_array[j] =  ft_strdup(env[i]); 
            j++;
        }
        i++;
    }
    smaller_array[j] = NULL ; 
    //ft_free_split(env);
    return smaller_array;   
}

int main(int argc , char **argv , char **env )
{

    int i ; 
    int array_size ; 
    char **new_env ; 
    char **added_data ;
    char **removed ; 

    i = 0 ; 
    array_size = calculate_array_size(env) ; 
    new_env = malloc(sizeof(char*) * (array_size + 1 )) ; 
    while(env[i])
    {
        new_env[i] = ft_strdup(env[i]) ;
        i++;
    }
    new_env[i] = NULL ; 
    added_data = ft_export(new_env , "test=1337") ; 
    removed = ft_unset(added_data  , "ZSH");
    i = 0 ; 
    while(added_data[i])
    {
        printf("%s\n" , added_data[i]);
        i++;
    }
    i = 0 ;

    printf("_________________________________") ; 
   
   while(removed[i])
    {
        printf("%s\n" , removed[i]);
        i++;
    } 
    return 0 ; 




}