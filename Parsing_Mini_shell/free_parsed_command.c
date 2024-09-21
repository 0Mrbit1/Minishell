#include <stdlib.h>
#include "mini_shell.h"
 
void free_parsed_command(t_command *cmd)
{
    t_command *temp;

    while (cmd)
    {
        temp = cmd;
        cmd = cmd->next;

   
        if (temp->command)
            free(temp->command);

 
        if (temp->args)
        {
            int i = 0; 
            while (temp->args[i] != NULL)
                {
                    free(temp->args[i]);
                    i++;
                }
            free(temp->args);
        }
         if (temp->input_redirect)
            free(temp->input_redirect);
        if (temp->output_redirect)
            free(temp->output_redirect);
        free(temp);
    }
}
