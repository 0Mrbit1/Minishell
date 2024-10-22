#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mini_shell.h"


t_env *env_list = NULL;  // Initialize the custom environment list


// Split "var=value" into key and value
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
            strncpy(*key, input, key_len);  // Copy key part before '='
            (*key)[key_len] = '\0';         // Null-terminate key
            strcpy(*value, equal_sign + 1); // Copy value part after '='
        }
        else
        {
            free(*key);  // Handle memory allocation failure
            free(*value);
            *key = NULL;
            *value = NULL;
        }
    }
    else
    {
        *key = NULL;
        *value = NULL;
    }
}

char *expand_variable(char *var_name, char **env)
{
    // First, check custom shell environment (env_list)
    t_env *current = env_list;
    while (current)
    {
        if (strcmp(current->key, var_name) == 0)
        {
            //printf("Match found in shell env for %s: %s\n", var_name, current->value);  // Debug print
            return strdup(current->value);  // Return the shell variable's value
        }
        current = current->next;
    }

    // If not found, check system environment (env[])
    for (int i = 0; env[i]; i++)
    {
        if (strncmp(env[i], var_name, strlen(var_name)) == 0 && env[i][strlen(var_name)] == '=')
        {
           // printf("Match found in system env for %s: %s\n", var_name, env[i] + strlen(var_name) + 1);  // Debug print
            return strdup(env[i] + strlen(var_name) + 1);  // Return system environment variable's value
        }
    }

   // printf("No match found for %s in environment variables\n", var_name);  // Debug if no match
    return NULL;
}



// Ensure that expanded variables are freed correctly and only once

void handle_variable_expansion(char *token, char **env)
{
    char *expanded_value = expand_variable(token + 1, env);  // Expand the variable, if exists

    if (expanded_value)
    {
        printf("Expanded value: %s\n", expanded_value);
        free(expanded_value);  // Free the expanded value after use
    }
}

