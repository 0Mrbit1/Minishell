#include "mini_shell.h" 

// void free_command(t_command *cmd)
// {
//     if (!cmd)
//         return;

//     // Free command
//     free(cmd->command);

//     // Free arguments
//     for (int i = 0; cmd->args && cmd->args[i]; i++)
//     {
//         free(cmd->args[i]);
//     }
//     free(cmd->args);

//     // Free input redirection files
//     for (int i = 0; cmd->input_redirects && cmd->input_redirects[i]; i++)
//     {
//         free(cmd->input_redirects[i]);
//     }
//     free(cmd->input_redirects);

//     // Free output redirection files
//     for (int i = 0; cmd->output_redirects && cmd->output_redirects[i]; i++)
//     {
//         free(cmd->output_redirects[i]);
//     }
//     free(cmd->output_redirects);

//     // Free append modes
//     free(cmd->append_modes);

//     // Free the next command in the pipeline
//     free_command(cmd->next);

//     // Free the command structure itself
//     free(cmd);
// }


//ORIGINAL
// void free_parsed_command(t_command *cmd)
// {
//     t_command *temp;

//     while (cmd)
//     {
//         temp = cmd;
//         cmd = cmd->next;

   
//         if (temp->command)
//             free(temp->command);

 
//         if (temp->args)
//         {
//             int i = 0; 
//             while (temp->args[i] != NULL)
//                 {
//                     free(temp->args[i]);
//                     i++;
//                 }
//             free(temp->args);
//         }
//          if (temp->input_redirect)
//             free(temp->input_redirect);
//         if (temp->output_redirect)
//             free(temp->output_redirect);
//         free(temp);
//     }
// }
