#include "minishell.h"



typedef struct command_attibutes
{
    char *here_doc_file;
	char *input_file;
	char *output_file;
    short append_mode; 
	short pipe_connected;
    char *command;
    
    struct tokens *command_attibutes;

} commands_data;