#include "mini_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_ARGS_SIZE 1024 /// we can deal that later !?

 void free_command(t_command *cmd)
{
    if (!cmd) return;
    free(cmd->command);
    for (int i = 0; cmd->args && cmd->args[i]; i++)
        free(cmd->args[i]);
    free(cmd->args);
    free(cmd->input_redirect);
    free(cmd->output_redirect);
    free(cmd);
}

char *expand_inside_quotes(char *str)
{
    // Create a buffer to hold the expanded string (use double the size just in case)
    char *expanded_str = malloc(strlen(str) * 2);  
    char *current = expanded_str;

    while (*str)
    {
        if (*str == '$')  // Handle variable expansion
        {
            str++;  // Skip the '$'
            char *var_start = str;
            // Extract the variable name
            while (*str && (isalnum(*str) || *str == '_'))
                str++;

            char var_name[256];
            strncpy(var_name, var_start, str - var_start);
            var_name[str - var_start] = '\0';  // Null-terminate the variable name

            // Expand the variable
            char *expanded_value = expand_variable(var_name);  // Call expand_variable

            if (expanded_value)
            {
                strcpy(current, expanded_value);  // Copy the expanded value
                current += strlen(expanded_value);  // Move the pointer
                free(expanded_value);  // Free the expanded value
            }
        }
        else
        {
            *current++ = *str++;  // Copy regular characters
        }
    }

    *current = '\0';  // Null-terminate the expanded string
    return expanded_str;
}


    //  i creat that function to called it  after each command execution to avoid memory leaks && creates a new, larger array, copies the old contents into it, and frees the old array.
    //  it ensures the shell can handle an arbitrary number of arguments 
char **resize_args(char **old_args, int old_size, int new_size)
{   
    int i = 0;
    char **new_args = malloc(new_size * sizeof(char *));
    if (!new_args) return NULL;

    while( i < old_size)
    {
        new_args[i] = old_args[i];  // copy over the old arguments
        i++;
    }

    free(old_args);     // free the old array
    return new_args;    // for return the new and resized array
}
t_env *env_list = NULL;

/*
*
**/

/*1*/
t_command *parse_command(token *tokens)
{
    if (!tokens) 
    {
        return NULL;
    }
    
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd)
    {
        return NULL;
    }
    
    cmd->command = NULL;
    cmd->args = NULL;
    cmd->input_redirect = NULL;
    cmd->output_redirect = NULL;
    cmd->append_mode = 0;
    cmd->next = NULL;

    int arg_count = 0;
    int max_args = INITIAL_ARGS_SIZE;               
    cmd->args = malloc(max_args * sizeof(char *));
    if (!cmd->args)
    {
        free(cmd);
        return NULL;
    }

    while (tokens)
    {
        // Handle the command itself (first word)
        if (!cmd->command && tokens->token_type == WORD)
        {
            cmd->command = strdup(tokens->value);
            cmd->args[arg_count++] = strdup(cmd->command);
        }
        // Handle key-value pairs for export
        else if (strcmp(cmd->command, "export") == 0 && strchr(tokens->value, '='))
        {
            char *key = NULL, *val = NULL;
            split_key_value(tokens->value, &key, &val);
            if (key && val)
            {
                store_env_variable(key, val);  // Store in your environment structure
                cmd->args[arg_count++] = strdup(tokens->value);  // Add key=value to args for debugging/printing
                free(key);
                free(val);
            }
        }

        // Handle expandable variables (starting with $)
        else if (tokens->token_type == EXPANDABLE)
        {
            char *expanded_value = expand_variable(tokens->value + 1); // Skip the '$'
            if (expanded_value) {
                cmd->args[arg_count++] = expanded_value;
            }
        }

        // Handle quoted strings (e.g., "something")
        else if (tokens->token_type == QUOTED_STRING)
        {
            char *expanded_value = expand_inside_quotes(tokens->value); // Expand variables inside quotes
            if (expanded_value) {
                cmd->args[arg_count++] = expanded_value;
            }
        }
        
        // Handle words that start with double quotes (expansion inside)
        else if (tokens->token_type == WORD && tokens->value[0] == '"')
        {
            // Handle expansion inside double quotes
            char *expanded_value = expand_inside_quotes(tokens->value);
            cmd->args[arg_count++] = expanded_value;
        }

        // Handle normal words
        else if (tokens->token_type == WORD)
        {
            // Resize argument list if necessary
            if (arg_count >= max_args - 1)
            {
                int new_size = max_args * 2;
                char **new_args = resize_args(cmd->args, max_args, new_size);
                if (!new_args)
                {
                    free_command(cmd);
                    return NULL;
                }
                cmd->args = new_args;
                max_args = new_size;
            }
            cmd->args[arg_count++] = strdup(tokens->value);
        }

        // Handle input redirection
        else if (tokens->token_type == INPUT_REDIRECTION)
        {
            tokens = tokens->next;
            if (tokens && tokens->token_type == WORD)
                cmd->input_redirect = strdup(tokens->value); 
        }

        // Handle output redirection
        else if (tokens->token_type == OUTPUT_REDIRECTION || tokens->token_type == OUTPUT_REDIRECTION_APPEND_MODE)
        {
            cmd->append_mode = (tokens->token_type == OUTPUT_REDIRECTION_APPEND_MODE);
            tokens = tokens->next;
            if (tokens && tokens->token_type == WORD)
                cmd->output_redirect = strdup(tokens->value);
        }

        tokens = tokens->next;
    }

    cmd->args[arg_count] = NULL;  
    return cmd;
}

/*
 * Print the parsed command structure for debugging.
 */
 
void print_parsed_command(t_command *cmd)
{
    if (!cmd)
    {
        printf("No command parsed.\n");
        return;
    }

    printf("Command: %s\n", cmd->command);

    int i = 0;
    while (cmd->args && cmd->args[i])
    {
        printf("Arg[%d]: %s\n", i, cmd->args[i]);
        i++;
    }

    if (cmd->input_redirect)
    {
        printf("Input redirection: %s\n", cmd->input_redirect);
    }
    
    if (cmd->output_redirect)
    {
        printf("Output redirection: %s\n", cmd->output_redirect);
    }

    printf("Append mode: %d\n", cmd->append_mode);

    if (cmd->next)
    {
        printf("Next command (pipe):\n");
        print_parsed_command(cmd->next); // Recursively print the next command in the pipeline
    }
}
