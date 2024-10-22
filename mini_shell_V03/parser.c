#include "mini_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_REDIRECT_SIZE 4  // Initial size for redirection arrays
#define INITIAL_ARGS_SIZE 16



char **resize_array(char **old_array, int old_size, int new_size)
{
    char **new_array = malloc(new_size * sizeof(char *));
    if (!new_array) {
        return NULL;
    }

    // Copy old array content to new array
    for (int i = 0; i < old_size; i++) {
        new_array[i] = old_array[i];
    }

    // Free old array
    free(old_array);

    return new_array;
}

// Helper function to resize an int array (for append_modes)
int *resize_int_array(int *old_array, int old_size, int new_size)
{
    int *new_array = malloc(new_size * sizeof(int));
    if (!new_array) {
        return NULL;
    }

    // Copy old array content to new array
    for (int i = 0; i < old_size; i++) {
        new_array[i] = old_array[i];
    }

    // Free old array
    free(old_array);

    return new_array;
}


void free_command(t_command *cmd)
{
    if (cmd) {
        free(cmd->command);
        if (cmd->args) {
            for (int i = 0; cmd->args[i]; i++)
            {
                free(cmd->args[i]);
            }
            free(cmd->args);
        }
        if (cmd->input_redirects) {
            for (int i = 0; cmd->input_redirects[i]; i++)
            {
                free(cmd->input_redirects[i]);
            }
            free(cmd->input_redirects);
        }
        if (cmd->output_redirects)
        {
            for (int i = 0; cmd->output_redirects[i]; i++)
            {
                free(cmd->output_redirects[i]);
            }
            free(cmd->output_redirects);
        }
        free(cmd->append_modes);
        free(cmd);
    }
}
// Parse command function
t_command *parse_command(token *tokens, char **env)
{
    if (!tokens) return NULL;

    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd) return NULL;

    // Initialize the command structure
    cmd->command = NULL;
    cmd->args = malloc(INITIAL_ARGS_SIZE * sizeof(char *));
    cmd->input_redirects = malloc(INITIAL_REDIRECT_SIZE * sizeof(char *));
    cmd->output_redirects = malloc(INITIAL_REDIRECT_SIZE * sizeof(char *));
    cmd->append_modes = malloc(INITIAL_REDIRECT_SIZE * sizeof(int));
    cmd->next = NULL;

    if (!cmd->args || !cmd->input_redirects || !cmd->output_redirects || !cmd->append_modes) {
        free_command(cmd);
        return NULL;
    }

    int arg_count = 0, max_args = INITIAL_ARGS_SIZE;
    int input_count = 0, max_inputs = INITIAL_REDIRECT_SIZE;
    int output_count = 0, max_outputs = INITIAL_REDIRECT_SIZE;

    while (tokens) {
        // Handle the command name
        if (!cmd->command && (tokens->token_type == WORD || 
            tokens->token_type == DOUBLE_QUOTED_STRING || tokens->token_type == SINGLE_QUOTED_STRING)) {
            cmd->command = strdup(tokens->value);
            cmd->args[arg_count++] = strdup(cmd->command);
            tokens = tokens->next;
            continue;
        }

        // Handle arguments
        if (tokens->token_type == WORD || 
            tokens->token_type == DOUBLE_QUOTED_STRING || tokens->token_type == SINGLE_QUOTED_STRING) {
            char *arg_value = tokens->value;

            // Check for variable expansion
            if (arg_value[0] == '$') {
                char *var_name = arg_value + 1;  // Skip the '$'
                char *expanded_value = expand_variable(var_name, env);
                if (expanded_value) {
                    arg_value = expanded_value;  // Use the expanded value
                }
            }

            // Resize args array if necessary
            if (arg_count >= max_args - 1) {
                max_args *= 2;
                cmd->args = resize_array(cmd->args, arg_count, max_args);
                if (!cmd->args) {
                    free_command(cmd);
                    return NULL;
                }
            }
            cmd->args[arg_count++] = strdup(arg_value);
        }

        // Handle input redirection
        else if (tokens->token_type == INPUT_REDIRECTION) {
            tokens = tokens->next;  // Move to the file name
            if (tokens && (tokens->token_type == WORD || 
                tokens->token_type == DOUBLE_QUOTED_STRING || tokens->token_type == SINGLE_QUOTED_STRING)) {
                // Resize input_redirects array if necessary
                if (input_count >= max_inputs - 1) {
                    max_inputs *= 2;
                    cmd->input_redirects = resize_array(cmd->input_redirects, input_count, max_inputs);
                    if (!cmd->input_redirects) {
                        free_command(cmd);
                        return NULL;
                    }
                }
                cmd->input_redirects[input_count++] = strdup(tokens->value);
            } else {
                fprintf(stderr, "Error: No file specified for input redirection\n");
                free_command(cmd);
                return NULL;
            }
        }

        // Handle output redirection
        else if (tokens->token_type == OUTPUT_REDIRECTION || tokens->token_type == OUTPUT_REDIRECTION_APPEND_MODE) {
            int append = (tokens->token_type == OUTPUT_REDIRECTION_APPEND_MODE);
            tokens = tokens->next;  // Move to the file name
            if (tokens && (tokens->token_type == WORD || 
                tokens->token_type == DOUBLE_QUOTED_STRING || tokens->token_type == SINGLE_QUOTED_STRING)) {
                // Resize output_redirects and append_modes arrays if necessary
                if (output_count >= max_outputs - 1) {
                    max_outputs *= 2;
                    cmd->output_redirects = resize_array(cmd->output_redirects, output_count, max_outputs);
                    cmd->append_modes = resize_int_array(cmd->append_modes, output_count, max_outputs);
                    if (!cmd->output_redirects || !cmd->append_modes) {
                        free_command(cmd);
                        return NULL;
                    }
                }
                cmd->output_redirects[output_count] = strdup(tokens->value);
                cmd->append_modes[output_count] = append;
                output_count++;
            } else {
                fprintf(stderr, "Error: No file specified for output redirection\n");
                free_command(cmd);
                return NULL;
            }
        }

        tokens = tokens->next;
    }

    cmd->args[arg_count] = NULL;  // Null-terminate the args array
    cmd->input_redirects[input_count] = NULL;  // Null-terminate the input redirects array
    cmd->output_redirects[output_count] = NULL;  // Null-terminate the output redirects array

    return cmd;
}



token *tokenize_input(const char *input, char **env)
{
    token *head = NULL;
    token *current = NULL;
    const char *str = input;

    while (*str)
    {
        // Skip leading whitespace
        while (isspace(*str))
            str++;

        if (*str == '\0')
            break;

        char *token_value = NULL;
        token_type type;  // Declare a variable to hold the token type

        // Get the next token (handles quoted strings)
        token_value = next_token(&str, env, &type);  // Pass the type variable to next_token

        if (token_value == NULL)
            continue;  // Skip invalid or empty tokens

        // Create new token node
        token *new_token = malloc(sizeof(token));
        new_token->value = token_value;
        new_token->token_type = type;
        new_token->next = NULL;

        // Append to the token list
        if (!head)
            head = new_token;
        else
            current->next = new_token;
        current = new_token;
    }

    return head;
}

// 

//             //ORIGNAL
char *handle_quoted_string_with_expansion(char *str, char **env)
{
         printf("\nç@c HANDLE\n");

    char *expanded_str = malloc(strlen(str) * 2 + 1);
    if (!expanded_str)
        return NULL;

    char *current = expanded_str;

    while (*str)
    {
        if (*str == '\\')
        {
            str++;
            if (*str == '$' || *str == '`' || *str == '"' || *str == '\\')
            {
                // Escape sequences inside double quotes
                *current++ = *str++;
            }
            else
            {
                // Backslash followed by other characters: include the backslash literally
                *current++ = '\\';
                if (*str)
                    *current++ = *str++;
            }
        }
        else if (*str == '$')
        {
           // printf("Detected variable expansion: %s\n", str); // Debug
            str++;  // Skip the '$'
            char *var_start = str;

            // Extract the variable name
            while (*str && (isalnum(*str) || *str == '_'))
                str++;

            char var_name[256];
            strncpy(var_name, var_start, str - var_start);
            var_name[str - var_start] = '\0';

          //  printf("Expanding variable: %s\n", var_name);  // Debug

            // Expand the variable
            char *expanded_value = expand_variable(var_name, env);
            if (expanded_value)
            {
              //  printf("Expanded value: %s\n", expanded_value);  // Debug
                strcpy(current, expanded_value);
                current += strlen(expanded_value);
                free(expanded_value);
            } 
        }
        else
        {
            // Copy regular text
            *current++ = *str++;
        }
    }

    *current = '\0';  // Null-terminate the expanded string
                   //printf(" \nvariable '%s'  \n", current);  // Debug
    return expanded_str;
}

        // ORGIN
char *next_token(const char **str, char **env, token_type *type)
{
    // Skip leading whitespace
    while (isspace(**str))
        (*str)++;

    if (**str == '\0')
        return NULL;
    const char *start = *str;
// Handle 'echo' command

if (strncmp(start, "echo", 4) == 0 && (isspace(start[4]) || start[4] == '\0'))
{
    *str += 4;  // Move past 'echo'

    // Create a mutable copy of the remaining input
    char *remaining_input = strdup(*str);
    if (remaining_input == NULL)
    {
        // Handle memory allocation failure
        perror("strdup");
        exit(EXIT_FAILURE);
    }

    // Call handle_echo_command with the mutable copy
    handle_echo_command(remaining_input, env);  // Process the remaining input for echo
    free(remaining_input);  // Free the allocated memory for remaining_input
   // return NULL;  // Return NULL as we don't need to process further tokens
}
  

    // Handle quoted strings
    if (**str == '"' || **str == '\'')
    {
        char quote = **str;  // Get the quote character (' or ")
        (*str)++;  // Skip past the opening quote

        // Extract the quoted string
        const char *quoted_start = *str;
        while (**str && **str != quote)
            (*str)++;
        size_t len = *str - quoted_start;
        char *token_value = malloc(len + 1);
         strncpy(token_value, quoted_start, len);
        token_value[len] = '\0';

        if (**str == quote)
            (*str)++;  // Skip past the closing quote

        if (quote == '\'')
        {
            // Single-quoted string: No expansion
            *type = SINGLE_QUOTED_STRING;
            return token_value;
        }
         else
        {
            // Handle double-quoted strings with variable expansion
            *type = DOUBLE_QUOTED_STRING;
            char *expanded_token = handle_quoted_string_with_expansion(token_value, env);
            free(token_value);
            return expanded_token;
        }
    }

    // Handle redirection and pipes
    if (**str == '>' || **str == '<' || **str == '|')
    {
        char symbol = **str;
        (*str)++;  // Move past the symbol

        if (symbol == '>' && **str == '>')
        {
            (*str)++;  // Handle '>>'
            *type = OUTPUT_REDIRECTION_APPEND_MODE;
            return strdup(">>");
        }
        else if (symbol == '<' && **str == '<')
        {
            (*str)++;  // Handle '<<'
            *type = HERE_DOC;
            return strdup("<<");
        }
        else
        {
            char temp[2] = {symbol, '\0'};
            if (symbol == '>')
                *type = OUTPUT_REDIRECTION;
            else if (symbol == '<')
                *type = INPUT_REDIRECTION;
            else if (symbol == '|')
                *type = PIPES;
            return strdup(temp);
        }
    }

    // Handle regular tokens (commands and arguments)

    while (**str && !isspace(**str) && **str != '>' && **str != '<' && **str != '|' && **str != '\'' && **str != '"')
        (*str)++;

     size_t len = *str - start;
    char *token_value = malloc(len + 1);
     strncpy(token_value, start, len);
  

    token_value[len] = '\0';

if (token_value[0] == '$')
{           
 
     char *var_name = strdup(token_value + 1);  // Remove the $ symbol
     char *expanded_value = expand_variable(var_name, env);
    free(var_name);

    if (expanded_value)
    {
           
        free(token_value);  // Free the old token
        token_value = expanded_value;  // Use the expanded value
    }
    else
    { 
      
        free(token_value);
        token_value = strdup("");  // Return an empty string if variable not found
    }
    *type = EXPANDABLE;
}
else
{
    *type = WORD;
}
 
    return token_value;
}

/***********************/
