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
