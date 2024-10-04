#include "mini_shell.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mini_shell.h"
 
token *create_token(char *value, token_type type)
{
    token *new_token;

    new_token = malloc(sizeof(token));
    if (!new_token)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    new_token->value = strdup(value);
    if (!new_token->value)
    {
        perror("strdup");
        free(new_token);
        exit(EXIT_FAILURE);
    }
    new_token->token_type = type;
    new_token->next = NULL;
    return new_token;
}

token *setup_first_node(char **split_prompt, redir_func_ptr *redirection_functions)
{
    int j;
    token *first_node;

    j = 0;
    first_node = create_token(split_prompt[0], WORD); // default to WORD

    while (j < 6)
    {
        if (redirection_functions[j](split_prompt[0]))
        {
            free(first_node->value);
            free(first_node);
            first_node = create_token(split_prompt[0], j);
            break;
        }
        j++;
    }
    return first_node;
}

void setup_nodes(char **split_prompt, redir_func_ptr *redirection_functions, token **first_node, int i)
{
    token *node;
    int j;

    node = *first_node;
    while (split_prompt[i])
    {
        j = 0;
        int found = 0;  // flag to indicate if a special token type is found

        while (j < 6)
        {
            if (redirection_functions[j](split_prompt[i]))
            {
                node->next = create_token(split_prompt[i], j);
                node = node->next;
                found = 1;
                break;
            }
            j++;
        }

        if (!found)
        {
            node->next = create_token(split_prompt[i], WORD);
            node = node->next;
        }
        i++;
    }
}

// 
/*
ok*/

token *tokenizer(char *prompt)
{
    const char *str = prompt;
    token *first_node = NULL;
    token *current_node = NULL;
    redir_func_ptr redirection_functions[6];

    redirection_functions[0] = is_HERE_DOC;
    redirection_functions[1] = is_INPUT_REDIRECTION;
    redirection_functions[2] = is_OUTPUT_REDIRECTION_APPEND_MODE;
    redirection_functions[3] = is_OUTPUT_REDIRECTION;
    redirection_functions[4] = is_PIPES;
    redirection_functions[5] = is_WORD;

    while (*str)
    {
        char *value = next_token(&str);
        if (!value) break;

        int i = 0;
        token_type type = WORD;
        int expandable = 0;

        while (i < 6)
        {
            if (redirection_functions[i](value))
            {
                type = i;
                break;
            }
            i++;
        }

        if (value[0] == '$' || value[0] == '~')
        {
            expandable = 1;  // Mark as expandable
            type = EXPANDABLE;
        }

        token *new_node = malloc(sizeof(token));
        new_node->value = value;
        new_node->token_type = type;
        new_node->expandable = expandable;
        new_node->next = NULL;

        if (!first_node)
        {
            first_node = new_node;
            current_node = new_node;
        }
        else
        {
            current_node->next = new_node;
            current_node = new_node;
        }
    }

    return first_node;
}



/*
ok*/
/*******/

char *next_token(const char **str)
{
    // skip leading whitespace
    while (isspace(**str))
        (*str)++;

    // if the string is empty, return NULL
    if (**str == '\0')
        return NULL;

    // handle single characters like pipes or redirection symbols
    if (**str == '|' || **str == '<' || **str == '>')
    {
        char *token = malloc(2);
        token[0] = **str;
        token[1] = '\0';
        (*str)++;  // move past the special character
        return token;
    }

    // handle quoted strings
    if (**str == '"' || **str == '\'')  
        return extract_quoted_string(str);

    // start capturing the token
    const char *start = *str;
    while (**str && !isspace(**str) && **str != '|' && **str != '<' && **str != '>')
        (*str)++;

    size_t len = *str - start;
    char *token = (char *)malloc(len + 1);
    if (!token)
        return NULL;
    
    strncpy(token, start, len);
    token[len] = '\0';  // Null-terminate the token
    
    return token;
}


/*
 * extract a quoted string, returning the content inside the quotes.
 *
 */
// extracts the full content of a quoted string, handling single (') and double (")
char *extract_quoted_string(const char **str)
{
    char quote = **str;  // Capture whether it's ' or "
    (*str)++;  // Move past the opening quote
    const char *start = *str;

    // Move until the closing quote is found
    while (**str && **str != quote)
        (*str)++;

    if (**str != quote) {
        printf("Error: Unmatched quote detected.\n");
        return NULL;  // Handle unmatched quotes (optional)
    }

    size_t len = *str - start;
    char *quoted_string = (char *)malloc(len + 1);
    strncpy(quoted_string, start, len);
    quoted_string[len] = '\0';

    (*str)++;  // Move past the closing quote

    return quoted_string;
}

/*
 * Extract the next token, handling quoted strings as a single token.
 */

/*************/

void free_token_list(token *head)
{
    token *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp->value);
        free(temp);
    }
}
