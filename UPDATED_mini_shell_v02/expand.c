#include "mini_shell.h"

int calculate_array_size(char **array)
{
    int i = 0;
    while(array[i])
        i++;
    return i;
}


char **expand_array(char **last_array)
{
    int i = 0;
    char **new_array;
    int array_size = calculate_array_size(last_array);

    new_array = malloc(sizeof(char*) * (array_size + 2)); // +1 for the new entry, +1 for the NULL terminator

    while (last_array[i])
    {
        new_array[i] = strdup(last_array[i]); // Copy over the old values
        i++;
    }
    new_array[i] = NULL; // Null-terminate the new array
    ft_free_split(last_array); // Free the old array
    return new_array;
}

char **ft_export(char **last_env, char *variable)
{
    char **bigger_env = expand_array(last_env);
    int i = 0;

    while (bigger_env[i]) // Find the last entry in the environment array
    {
        i++;
    }

    bigger_env[i] = strdup(variable); // Add the new variable to the last slot
    i++;
    bigger_env[i] = NULL; // Null-terminate the array
    return bigger_env;
}


int ft_strlen_delimiter(char *str, char delimiter)
{
    int i = 0;
    while (str[i] && (str[i] != delimiter))
    {
        i++;
    }
    return i;
}

int search_key(char **env, char *to_search)
{
    int i = 0;
    while (env[i])
    {
        if (!strncmp(env[i], to_search, ft_strlen_delimiter(env[i], '=')))
        {
            return i; // Return the index if the key matches
        }
        i++;
    }
    return -1; // Return -1 if the key is not found
}


char **ft_unset(char **env, char *var)
{
    int i = 0, j = 0;
    int key = search_key(env, var); // Find the index of the variable to remove
    int array_size = calculate_array_size(env);
    char **smaller_array = malloc(sizeof(char*) * (array_size)); // Allocate memory for the new array

    while (env[i])
    {
        if (i != key) // Copy everything except the variable to be removed
        {
            smaller_array[j] = strdup(env[i]);
            j++;
        }
        i++;
    }
    smaller_array[j] = NULL; // Null-terminate the array
    //ft_free_split(env);  // Free the old environment array (commented out here)
    return smaller_array;
}


/*int main(int argc , char **argv , char **env )
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
}*/