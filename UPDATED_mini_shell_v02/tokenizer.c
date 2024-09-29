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

/***************/

token *setup_first_node(char **split_prompt, redir_func_ptr *redirection_functions)
{
    int j;
    token *first_node;

    j = 0;
    first_node = create_token(split_prompt[0], WORD);  

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

/***************/

void setup_nodes(char **split_prompt, redir_func_ptr *redirection_functions, token **first_node, int i)
{
    token *node;
    int j;

    node = *first_node;
    while (split_prompt[i])
    {
        j = 0;
        int found = 0;   

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

/***************/

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

        while (i < 6)
        {
            if (redirection_functions[i](value))
            {
                type = i;
                break;
            }
            i++;
        }

        token *new_node = malloc(sizeof(token));
        new_node->value = value;
        new_node->token_type = type;
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

/*******/

char *next_token(const char **str)
{
     
    while (isspace(**str))
        (*str)++;

     if (**str == '\0')
        return NULL;

     if (**str == '|' || **str == '<' || **str == '>')
    {
        char *token = malloc(2);
        token[0] = **str;
        token[1] = '\0';
        (*str)++;   
        return token;
    }

 
    if (**str == '"' || **str == '\'')  
        return extract_quoted_string(str);

 
    const char *start = *str;
    while (**str && !isspace(**str) && **str != '|' && **str != '<' && **str != '>')
        (*str)++;

    size_t len = *str - start;
    char *token = (char *)malloc(len + 1);
    if (!token)
        return NULL;
    
    strncpy(token, start, len);
    token[len] = '\0';   
    
    return token;
}

/********#*******/
/**-----------**/
/********#******/
char *extract_quoted_string(const char **str)
{
    char quote = **str;
    (*str)++;
    const char *start = *str;
    size_t total_len = 0;
    size_t current_buffer_size = 128; // start with an initial buffer size
    char *quoted_string = malloc(current_buffer_size);
    if(!quoted_string)
    {
        printf("error allocation.\n");
        return NULL;
    }
    quoted_string[0] = '\0'; //start with an empty string
    while(1337)
    {
        // moving until the closing quote is found or end of input
        while(**str && **str != quote)
        {
            (*str)++;
        }
        size_t len = *str - start;
        total_len += len;
        // check for if we need to increase the buffer size manually
     if (total_len >= current_buffer_size - 1)
        {
            char *new_quoted_string = malloc(total_len + 1 + 128); // allocate for a bigger buffer
            if(!new_quoted_string)
            {
                printf("Memory allocation error.\n");
                free(quoted_string);
                return NULL;
            }
            strcpy(new_quoted_string, quoted_string);
            free(quoted_string);
            quoted_string = new_quoted_string;
            current_buffer_size = total_len + 1 + 128;
        }
        // append the current part for quoted string
        strncat(quoted_string, start, len);
        // if we found the closing quote  break
        if(**str == quote)
        {
            (*str)++; //move past the closing quote
            break;
        }
        //asking for more input
        char *additional_input = readline("quote> ");
        if(additional_input == NULL)
        {
            printf("Error: unmatched quote detected and no more input.\n");
            free(quoted_string);
            return NULL;
        }
        // update start to point to the new input for  processing
        start = additional_input;
        *str = additional_input;
    }
    return quoted_string;
}
 /*************/
/*-------------*/
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
