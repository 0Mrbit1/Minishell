#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

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
    char            *value;          // The token string value
    token_type      token_type;      // The type of token
    struct s_token  *next;           // Pointer to the next token in the list
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

/**** */
char	*ft_strjoin(char const *s1, char const *s2);
pid_t first_child_processe(t_command *prompt  ,  char *cmd_path , char **argv , char **env, int **pipefd , int j );
pid_t middle_child_processes(t_command *prompt  , char *cmd_path , char **argv ,  int **pipefd , char **env , int j );
pid_t ending_child_processe(t_command *prompt , char *cmd_path , char **argv , int **pipefd , char **env , int j );
void    is_exit_with_signal(int *status);
int     pipex(t_command *prompt , char **env);
void    dup_fds(int old_fd , int new_fd);
void output_redirection(char *file_path);
void redidrect_stdin_to_herdoc(char *delimiter );
void input_redirection_herdoc(char *delimiter );
void execute_command(char *command_path , char **argv , char **env);
void output_error_exit(char *error_msg , int status);
char	*is_command(char *cmd, char **env);
char ft_cd(char* path);
char	*cmd_helper(char *cmd, char *PATH_VARIABLE);
char	*get_command_path(char *cmd, char *PATH_VARIABLE);
void 	ft_free_split(char **split);


/**** */
t_command *parse_command(token *tokens, char **env);

void print_parsed_command(t_command *cmd);
void execute_pipeline(t_command *cmd_list);
char *expand_variable(const char *token, char **env);

/* Lexer and parser functions */
    typedef int (*redir_func_ptr)(char *token);
token *tokenizer(char *prompt);
 
/* Function declarations */
char *extract_quoted_string(const char **str);
char *next_token(const char **str);
token *tokenizer(char *prompt);
token_type identify_token_type(char *token_value);

// print_parsed_command
//  void print_parsed_command(t_command *cmd);
 void execute_pipeline(t_command *cmd_list);

void free_parsed_command(t_command *cmd);
void free_token_list(token *head);
// char    **ft_split(const char *str, char c);
void    shell_loop(void);
token   *tokenizer(char *prompt);
void    print_tokens(token *head);
void    free_token_list(token *head);
token   *setup_first_node(char **split_prompt, redir_func_ptr *redirection_functions);
void    setup_nodes(char **split_prompt, redir_func_ptr *redirection_functions, token **first_node, int i);
char	**ft_split(const char *str, char *delimiters);


int     is_HERE_DOC(char *token);
int     is_INPUT_REDIRECTION(char *token);
int     is_OUTPUT_REDIRECTION_APPEND_MODE(char *token);
int     is_OUTPUT_REDIRECTION(char *token);
int     is_PIPES(char *token);
int     is_WORD(char *token);

#endif
        