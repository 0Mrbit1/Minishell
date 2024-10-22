#include "mini_shell.h"
#include <sys/wait.h>

int ft_lstsize(t_command *lst)
{
    int lst_size = 0;
    while (lst) {
        lst_size++;
        lst = lst->next;
    }
    return lst_size;
}
 

pid_t handle_child_process(t_command *prompt, char *cmd_path, char **argv, char **env, int **pipefd, int j, int lst_size) 
{
    pid_t pid;
    int fd;

    if (!strcmp(prompt->command, "cd")) 
    {
        ft_cd((prompt->args)[1]);
        return 0;
    }

    if (!strcmp(prompt->command, "export"))
     {
        printf("\n@@ Handling export command\n");

        for (int i = 1; prompt->args[i]; i++) 
        {
             handle_export_command(prompt->args[i],env);  // Pass the entire argument array and env
        }
        return 0;
    }

    // Fork a new process
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Child process
        // Handle pipe redirections based on the position in the pipeline
        if (j > 0) {
            dup2(pipefd[j - 1][0], STDIN_FILENO); // Input from the previous pipe
        }
        if (j < lst_size - 1) {
            dup2(pipefd[j][1], STDOUT_FILENO); // Output to the current pipe
        }

        // Close all pipe file descriptors in child
        for (int i = 0; i < lst_size - 1; i++) {
            close(pipefd[i][0]);
            close(pipefd[i][1]);
        }

        // Handle input redirections
        for (int i = 0; prompt->input_redirects && prompt->input_redirects[i]; i++) {
            fd = open(prompt->input_redirects[i], O_RDONLY);
            if (fd < 0) {
                perror(prompt->input_redirects[i]);
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }

        // Handle output redirections
        for (int i = 0; prompt->output_redirects && prompt->output_redirects[i]; i++) {
            if (prompt->append_modes[i]) {
                fd = open(prompt->output_redirects[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
            } else {
                fd = open(prompt->output_redirects[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            }
            if (fd < 0) {
                perror(prompt->output_redirects[i]);
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        execute_command(cmd_path, argv, env);
        exit(EXIT_FAILURE);  // Exit if execve fails
    }

    return pid;
}



pid_t middle_child_processes(t_command *prompt, char *cmd_path, char **argv, int **pipefd, char **env, int j)
 {
    pid_t pid;
    int fd;
    
    if (!strcmp(prompt->command, "cd"))
    {
        ft_cd((prompt->args)[1]);
        return 0;
    }
    // Fork a new process
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {  // Child process
        dup2(pipefd[j - 1][0], STDIN_FILENO);
        dup2(pipefd[j][1], STDOUT_FILENO);
        close(pipefd[j - 1][1]);
        close(pipefd[j][0]);
        // printf("Middle Child PID %d: Input from pipe %d and output to pipe %d\n", getpid(), j - 1, j);

        // Handle input redirections
        for (int i = 0; prompt->input_redirects && prompt->input_redirects[i]; i++)
        {
            fd = open(prompt->input_redirects[i], O_RDONLY);
            if (fd < 0) {
                perror(prompt->input_redirects[i]);
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
            // printf("Middle Child PID %d: Redirecting input from %s\n", getpid(), prompt->input_redirects[i]);
        }

        // Handle output redirections
        for (int i = 0; prompt->output_redirects && prompt->output_redirects[i]; i++) {
            if (prompt->append_modes[i]) {
                fd = open(prompt->output_redirects[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
                // printf("Middle Child PID %d: Appending output to %s\n", getpid(), prompt->output_redirects[i]);
            } else {
                fd = open(prompt->output_redirects[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                // printf("Middle Child PID %d: Redirecting output to %s\n", getpid(), prompt->output_redirects[i]);
            }
            if (fd < 0) {
                perror(prompt->output_redirects[i]);
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        close(pipefd[j - 1][0]);
        close(pipefd[j][1]);
        execute_command(cmd_path, argv, env);
    }
    return pid;
}

pid_t ending_child_process(t_command *prompt, char *cmd_path, char **argv, int **pipefd, char **env, int j) 
{
    pid_t pid;
    int fd;

    if (!strcmp(prompt->command, "cd"))
    {
        ft_cd((prompt->args)[1]);
        return 0;
    }
    // Fork a new process
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
     {  // Child process
        dup2(pipefd[j - 1][0], STDIN_FILENO);
        close(pipefd[j - 1][1]);
        // printf("Ending Child PID %d: Input from pipe %d\n", getpid(), j - 1);

        // Handle input redirections
        for (int i = 0; prompt->input_redirects && prompt->input_redirects[i]; i++) 
        {
            fd = open(prompt->input_redirects[i], O_RDONLY);
            if (fd < 0)
            {
                perror(prompt->input_redirects[i]);
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
            // printf("Ending Child PID %d: Redirecting input from %s\n", getpid(), prompt->input_redirects[i]);
        }

        // Handle output redirections
        for (int i = 0; prompt->output_redirects && prompt->output_redirects[i]; i++) 
        {
            if (prompt->append_modes[i])
             {
                fd = open(prompt->output_redirects[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
                // printf("Ending Child PID %d: Appending output to %s\n", getpid(), prompt->output_redirects[i]);
            } else {
                fd = open(prompt->output_redirects[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                // printf("Ending Child PID %d: Redirecting output to %s\n", getpid(), prompt->output_redirects[i]);
            }
            if (fd < 0) {
                perror(prompt->output_redirects[i]);
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        execute_command(cmd_path, argv, env);
    }
    return pid;
}


int pipex(t_command *prompt, char **env)
 {
    int lst_size = ft_lstsize(prompt);
    int **pipefd;
    int status;
    char *cmd_path;
    pid_t pid;
    int j = 0;

    // Allocate pipes
    pipefd = malloc(sizeof(int *) * (lst_size - 1));
    if (!pipefd) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < lst_size - 1; i++) 
    {
        pipefd[i] = malloc(sizeof(int) * 2);
        if (pipe(pipefd[i]) < 0) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    // Iterate over each command in the pipeline
    while (prompt) 
    {
        cmd_path = is_command(prompt->command, env);
        if (!cmd_path)
        {
            cmd_path = prompt->command;
        }

        pid = handle_child_process(prompt, cmd_path, prompt->args, env, pipefd, j, lst_size);

        // Move to the next command in the pipeline
        prompt = prompt->next;
        j++;
    }

    // Close all pipes in parent process
    for (int i = 0; i < lst_size - 1; i++)
    {
        close(pipefd[i][0]);
        close(pipefd[i][1]);
    }

    // Wait for all child processes
    for (int i = 0; i < lst_size; i++)
    {
        wait(&status);
    }

    // Free pipe file descriptors
    for (int i = 0; i < lst_size - 1; i++)
    {
        free(pipefd[i]);
    }
    free(pipefd);

    return 0;
}

 
void    is_exit_with_signal(int *status)
{
    if (WIFEXITED(*status))
        *status = WEXITSTATUS(*status);
    else if (WIFSIGNALED(*status))
        *status = WTERMSIG(*status) + 128;
} 

int main(int argc , char **argv , char **env)
{
   
    (void)argc;
    (void)argv;

    shell_loop(env);

    return 0;
}

void shell_loop(char **env) 
{
    char *line;
    token *tokens;
    t_command *parsed_command;

    while (1) 
    {
        printf("\n+-+\n");
        line = readline("Mini_shell(*-*)> ");  // Prompt for input
        if (!line)
        {
            printf("\nexit\n");
            exit(0);
        }

        // Check for unmatched quotes with escape sequence handling
        int in_single_quote = 0;
        int in_double_quote = 0;
        int escaped = 0;

        // Iterate through the input line to detect unmatched quotes and escape sequences
        for (char *ptr = line; *ptr; ptr++) 
        {
            if (escaped)
             {
                escaped = 0;  // After an escaped character, reset the escape flag
            }
            else if (*ptr == '\\')
            {
                escaped = 1;  // Set the escape flag
            } else if (*ptr == '\'' && !in_double_quote)
             {
                in_single_quote = !in_single_quote;  // Toggle single quotes when outside of double quotes
            } else if (*ptr == '"' && !in_single_quote)
             {
                in_double_quote = !in_double_quote;  // Toggle double quotes when outside of single quotes
            }
        }

        // If unmatched quotes are found, prompt for more input
        while (in_single_quote || in_double_quote)
         {
            char *continuation = readline("> ");  // Continue prompting for input
            char *new_line = malloc(strlen(line) + strlen(continuation) + 2);
            strcpy(new_line, line);
            strcat(new_line, "\n");  // Add newline between inputs
            strcat(new_line, continuation);

            free(line);  // Free previous input
            line = new_line;
            free(continuation);  // Free the continuation input

            // Recheck for unmatched quotes after adding new input
            in_single_quote = 0;
            in_double_quote = 0;
            escaped = 0;

            for (char *ptr = line; *ptr; ptr++)
            {
                if (escaped)
                {
                    escaped = 0;
                }
                else if (*ptr == '\\')
                 {
                    escaped = 1;
                } else if (*ptr == '\'' && !in_double_quote)
                {
                    in_single_quote = !in_single_quote;
                } else if (*ptr == '"' && !in_single_quote) {
                    in_double_quote = !in_double_quote;
                }
            }
        }

        // If the input is empty, continue the loop without processing
        if (line[0] == '\0')
        {
            free(line);
            continue;
        }
        else
        {
            // Tokenize the input line for general commands
            tokens = tokenize_input(line, env);  // Updated function name
            if (tokens)
            {
                // Parse the tokens into a command structure
                parsed_command = parse_command(tokens, env);
                
                // Execute the parsed commands
                pipex(parsed_command, env);

                // Free the parsed command and token list
                free_token_list(tokens);
                free_command(parsed_command);
            }
        }
        add_history(line);  // Store the input in history
        free(line);  // Free the line buffer
    }
}