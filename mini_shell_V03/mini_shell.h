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
#include <ctype.h>  

// token.h

typedef enum {
    WORD,
    EXPANDABLE,
    INPUT_REDIRECTION,
    OUTPUT_REDIRECTION,
    OUTPUT_REDIRECTION_APPEND_MODE,
    PIPES,
    HERE_DOC,
    SINGLE_QUOTED_STRING,
    DOUBLE_QUOTED_STRING
} token_type;

typedef struct token
{
    char *value;
    token_type token_type;
    struct token *next;
} token;

typedef struct s_command
{
    char *command;            // The command name
    char **args;              // Arguments for the command
    char **input_redirects;    // Array of input redirection files (e.g., < file1 < file2)
    char **output_redirects;   // Array of output redirection files (e.g., > file1 > file2)
    int *append_modes;         // Corresponding append modes (0 for '>', 1 for '>>')
    struct s_command *next;    // Pointer to the next command (for piped commands)
} t_command;


typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
} t_env;


int is_valid_variable_name(const char *name);

char *trim_whitespace(char *str);


/**/
void free_command(t_command *cmd);
void free_parsed_command(t_command *cmd);
t_command *parse_command(token *tokens, char **env);
token *tokenize_input(const char *input, char **env);
 t_command *initialize_command();
void shell_loop(char **env);
 
/**/
void free_tokens(token *head);
 

/***/
char *next_token(const char **str, char **env, token_type *type);
char *extract_quoted_string(const char **str);

extern t_env *env_list;
 
void store_env_variable(char *key, char *value);
char *handle_quoted_string_with_expansion(char *str, char **env);
char *expand_variable(char *var_name, char **env);
 
void handle_export_command(char *input, char **env);
 

/**** */
char	*ft_strjoin(char const *s1, char const *s2);
pid_t handle_child_process(t_command *prompt, char *cmd_path, char **argv, char **env, int **pipefd, int j, int lst_size);
// pid_t first_child_processe(t_command *prompt  ,  char *cmd_path , char **argv , char **env, int **pipefd , int j );
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
char *test_handle_echo_command(char *input, char **env);

 void handle_echo_command(char *input, char **env);
 pid_t handle_child_process(t_command *prompt, char *cmd_path, char **argv, char **env, int **pipefd, int j, int lst_size);
/**** */
t_command *parse_command(token *tokens, char **env);

void print_parsed_command(t_command *cmd);
void execute_pipeline(t_command *cmd_list);
 
typedef int (*redir_func_ptr)(char *token);
token *tokenizer(char *prompt, char **env);
void split_key_value(char *input, char **key, char **value);
token_type identify_token_type(char *token_value);
void free_token_list(token *head);
 void    print_tokens(token *head);
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
        