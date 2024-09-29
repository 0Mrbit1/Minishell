#include "mini_shell.h"
#include <string.h>
#include <stdlib.h>

char *expand_variable(const char *token, char **env)
{
    int i = 0;
    const char *var_name = token + 1;
    int y = strlen(var_name);
    
    while( env[i] != NULL)
    {
        if (strncmp(env[i], var_name, strlen(var_name)) == 0 && env[i][y] == '=')
        {
                       return strdup(env[i] + strlen(var_name) + 1);
        }
         i++;
    }

    return strdup("");
}
