#include <stdlib.h>
#include "mini_shell.h"

void split_key_value(char *input, char **key, char **value)
{
    char *equal_sign = strchr(input, '=');
    if (equal_sign)
    {
        int key_len = equal_sign - input;
        int val_len = strlen(equal_sign + 1);

        *key = malloc(key_len + 1);
        *value = malloc(val_len + 1);

        if (*key && *value)
        {
            strncpy(*key, input, key_len);
            (*key)[key_len] = '\0';

            strcpy(*value, equal_sign + 1);
        }
    }
}

void store_env_variable(char *key, char *value)
{
    t_env *current = env_list;

    // Check if the variable already exists in the list
    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            // Variable exists, update its value
            free(current->value);  // Free the old value
            current->value = strdup(value);  // Set new value
            return;
        }
        current = current->next;
    }

    // If the variable doesn't exist, add it to the environment list
    t_env *new_env = malloc(sizeof(t_env));
    if (!new_env)
        return;

    new_env->key = strdup(key);
    new_env->value = strdup(value);
    new_env->next = env_list;
    env_list = new_env;
}
/*
      char *expand_variable(char *value) 
      {
      
      }
*/
