#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
 
typedef enum e_token_type
{
    HERE_DOC,
    INPUT_REDIRECTION,
    OUTPUT_REDIRECTION_APPEND_MODE,
    OUTPUT_REDIRECTION,
    PIPES,
    WORD
} token_type;

 typedef struct s_token 
{
    char            *value;          
    token_type      token_type;       
    struct s_token  *next;           
} token;

 typedef struct s_command
{
    char *command;            
    char **args;              
    char *input_redirect;     
    char *output_redirect;     
    int append_mode;           
    struct s_command *next;    
} t_command;

typedef int (*redir_func_ptr)(char *token);
void setup_nodes(char **split_prompt, redir_func_ptr *redirection_functions, token **first_node, int i);
token *setup_first_node(char **split_prompt, redir_func_ptr *redirection_functions);
token *tokenizer(char *prompt);
char *next_token(const char **str);
char *extract_quoted_string(const char **str);
void free_token_list(token *head);

token *tokenizer(char *prompt);
void    print_parsed_command(t_command *cmd);
void    free_parsed_command(t_command *cmd);
char    **ft_split(const char *str, char c);
t_command *parse_command(token *tokens);

int     is_HERE_DOC(char *token);
int     is_INPUT_REDIRECTION(char *token);
int     is_OUTPUT_REDIRECTION_APPEND_MODE(char *token);
int     is_OUTPUT_REDIRECTION(char *token);
int     is_PIPES(char *token);
int     is_WORD(char *token);

#endif
