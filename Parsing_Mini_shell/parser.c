#include "mini_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL_ARGS_SIZE 1024  /// we can deal we that later !?

void free_command(t_command *cmd)
{
    int i = 0;
    if (!cmd) return;
    free(cmd->command);
    while(cmd->args && cmd->args[i])
        {
            free(cmd->args[i]);
            i++;
        }
    free(cmd->args);
    free(cmd->input_redirect);
    free(cmd->output_redirect);
    free(cmd);
}

 /*  
    i creat that function to called it  after each command execution to avoid memory leaks &&
     creates a new larger array copies the old contents into it  and frees the old array.
     it ensures the shell can handle an arbitrary number of arguments 
*/

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

/*************************/

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
    // initialization for command structure
    cmd->command = NULL;
    cmd->args = NULL;
    cmd->input_redirect = NULL;
    cmd->output_redirect = NULL;
    cmd->append_mode = 0;
    cmd->next = NULL;

    int arg_count = 0;
    int max_args = INITIAL_ARGS_SIZE;               // initial size for the argument array 'i defined above in header'// 
    cmd->args = malloc(max_args * sizeof(char *));
    if (!cmd->args)
    {
        free(cmd);
        return NULL;
    }

    while (tokens)
    {
        if (tokens->token_type == WORD)
        {
            if (!cmd->command)
            {
                // first is the command    //----- 
                cmd->command = strdup(tokens->value);
                cmd->args[arg_count++] = strdup(cmd->command);  // store the command as the first argument
            }
            else
            {
                if (arg_count >= max_args - 1)
                {
                    // manually resize the argument array
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
        }
          // and here it will detectig redirection tokens and it expects the next token to be the filename
        else if (tokens->token_type == INPUT_REDIRECTION)
        {
            tokens = tokens->next;
            if (tokens && tokens->token_type == WORD)
                cmd->input_redirect = strdup(tokens->value); // input redirection
            else
            {
                free_command(cmd);  
                return NULL;
            }
        }
        else if (tokens->token_type == OUTPUT_REDIRECTION || tokens->token_type == OUTPUT_REDIRECTION_APPEND_MODE) 
        {
            cmd->append_mode = (tokens->token_type == OUTPUT_REDIRECTION_APPEND_MODE);
            tokens = tokens->next;
            if (tokens && tokens->token_type == WORD)
                cmd->output_redirect = strdup(tokens->value); // output redirection
            else
            {
                free_command(cmd); 
                return NULL;
            }
        }
        else if (tokens->token_type == PIPES)
        {
            cmd->next = parse_command(tokens->next); // handle pipes (next command)
            break;
        }

        tokens = tokens->next;
    }

    cmd->args[arg_count] = NULL;  // Null-terminate the arguments array
    return cmd;
}


void print_parsed_command(t_command *cmd)
{
    while (cmd)
    {
        int i = 0;
        printf("command: %s\n", cmd->command);
        printf("arguments: ");
        while (cmd->args[i] != NULL)
        {
            printf("%s ", cmd->args[i]);
            i++;
        }
        printf("\n");

        if (cmd->input_redirect)
            printf("input_Redirection: %s\n", cmd->input_redirect);
        if (cmd->output_redirect)
            printf("output_Redirection: %s\n", cmd->output_redirect);
         printf("\n");
        cmd = cmd->next;  // move to the next command (for pipes)
    }
}