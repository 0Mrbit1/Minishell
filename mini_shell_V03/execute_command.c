#include "mini_shell.h"

void execute_command(char *command_path, char **argv, char **env) 
{
    if (execve(command_path, argv, env) < 0)
    {
        output_error_exit("command", 127); // This function should handle the error and exit
    }
}