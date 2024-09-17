#include "minishell.h"


#ifndef EXEC_H
# define EXEC_H


pid_t output_redirection(char *file_path , char *cmd_path , char **argv , char **env); 
int pipex(int argc , char **argv , char **env); 
 pid_t output_redirection_append_mode(char *file_path , char *cmd_path  , char **argv , char **env);
void output_error_exit(char *error_msg , int status);
pid_t  input_redirection (char *file_path , char *cmd_path , char **argv , char **env);
void input_redirection_herdoc(char *delimiter  , char *cmd_path , char **argv , char **env);
char	*is_command(char *cmd, char **env);
char **ft_unset(char **env  , char *var);
void execute_command(char *command_path , char **argv , char **env);
void dup_fds(int old_fd , int new_fd);
char ft_cd(char* path);
void ft_env(char **envp);
void ft_echo(int line , char *str);

#endif


