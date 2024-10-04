# ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef enum e_token_type
{
    HERE_DOC,
    INPUT_REDIRECTION,
    OUTPUT_REDIRECTION_APPEND_MODE,
    OUTPUT_REDIRECTION,
    PIPES,
    WORD,
    QUOTED_STRING,
    EXPANDABLE
} token_type;

typedef struct s_token 
{
    char            *value;          // The token string value
    token_type      token_type;      // The type of token
    int             expandable;      // New field to flag expandable tokens (0 or 1)
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

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
} t_env;

// global environment lis
/*
   by declaring it with extern in the header file  env_list is accessible across multiple source files. 
   This means any file that includes the header can access or modify the environment list making it a shared resource within the program
*/
//   ^^
extern t_env *env_list;

/**** */
char    *ft_strjoin(char const *s1, char const *s2);
pid_t first_child_processe(t_command *prompt, char *cmd_path, char **argv, char **env, int **pipefd, int j);
pid_t middle_child_processes(t_command *prompt, char *cmd_path, char **argv, int **pipefd, char **env, int j);
pid_t ending_child_processe(t_command *prompt, char *cmd_path, char **argv, int **pipefd, char **env, int j);
void     is_exit_with_signal(int *status);
int      pipex(t_command *prompt, char **env);
void     dup_fds(int old_fd, int new_fd);
void     output_redirection(char *file_path);
void     redidrect_stdin_to_herdoc(char *delimiter);
void     input_redirection_herdoc(char *delimiter);
// void execute_command(char *command_path, char **argv, char **env);
void    output_error_exit(char *error_msg, int status);
char    *is_command(char *cmd, char **env);
char    ft_cd(char *path);
char    *cmd_helper(char *cmd, char *PATH_VARIABLE);
char    *get_command_path(char *cmd, char *PATH_VARIABLE);
void    ft_free_split(char **split);
void    free_parsed_command(t_command *cmd);
// char *expand_inside_quotes(char *str, char **env);
char *expand_inside_quotes(char *str);
 
t_command *parse_command(token *tokens);


/**** */
pid_t middle_child_processes(t_command *cmd, char *cmd_path, char **argv, int **pipefd, char **env, int j);
pid_t first_child_processe(t_command *cmd, char *cmd_path, char **argv, char **env, int **pipefd, int j);
pid_t ending_child_processe(t_command *cmd, char *cmd_path, char **argv, int **pipefd, char **env, int j);

char *expand_variable(char *value);
void store_env_variable(char *key, char *value);
void split_key_value(char *input, char **key, char **value);
 
 
  
/***** */
 void free_command(t_command *cmd);
void print_parsed_command(t_command *cmd);
void execute_pipeline(t_command *cmd_list);

// char *expand_variable(char *value, char **env);
  
void free_command(t_command *cmd);

/* Lexer and parser functions */
typedef int (*redir_func_ptr)(char *token);
token *tokenizer(char *prompt);

/* Function declarations */
char *extract_quoted_string(const char **str);
char *next_token(const char **str);
token *tokenizer(char *prompt);
token_type identify_token_type(char *token_value);

void free_token_list(token *head);
void print_tokens(token *head);

int is_HERE_DOC(char *token);
int is_INPUT_REDIRECTION(char *token);
int is_OUTPUT_REDIRECTION_APPEND_MODE(char *token);
int is_OUTPUT_REDIRECTION(char *token);
int is_PIPES(char *token);
int is_WORD(char *token);

#endif
